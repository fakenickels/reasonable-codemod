open Reason_parser;
open Migrate_parsetree.Ast_404;
open Ast_helper;
open Ast_mapper;
open Asttypes;
open Parsetree;
open Longident;

type moduleLocation =
  | TopLevel
  | Nested(array(string));

module StringArrayMap =
  Map.Make({
    type t = moduleLocation;
    let compare = compare;
  });

let printModuleLocation =
  fun
  | TopLevel => "TopLevel"
  | Nested(keys) =>
    keys
    |> Array.fold_left(
         (acc, value) => (acc == "" ? acc : acc ++ ".") ++ value,
         "",
       );

let childrenUsageMap = ref(StringArrayMap.empty);

let logPrefix =
  Pastel.(<Pastel backgroundColor=Cyan color=Black> " UpgradeRR " </Pastel>);

let rec implementionMapStructureItem = (key, mapper, item) =>
  switch (item) {
  | {
      pstr_desc:
        Pstr_module(
          {
            pmb_name: {txt: moduleName},
            pmb_expr:
              {
                pmod_desc:
                  Pmod_functor(
                    name,
                    moduleType,
                    {pmod_desc: Pmod_structure(structure)} as moduleExpression,
                  ),
              } as functorExpression,
          } as moduleBinding,
        ),
    } as structureItem => {
      ...structureItem,
      pstr_desc:
        Pstr_module({
          ...moduleBinding,
          pmb_expr: {
            ...functorExpression,
            pmod_desc:
              Pmod_functor(
                name,
                moduleType,
                {
                  ...moduleExpression,
                  pmod_desc:
                    Pmod_structure(
                      structure
                      |> List.map(structureItem =>
                           implementionMapStructureItem(
                             switch (key) {
                             | TopLevel => Nested([|moduleName|])
                             | Nested(keys) =>
                               Nested(Array.concat([keys, [|moduleName|]]))
                             },
                             mapper,
                             structureItem,
                           )
                         ),
                    ),
                },
              ),
          },
        }),
    }
  | {
      pstr_desc:
        Pstr_module(
          {
            pmb_name: {txt: moduleName},
            pmb_expr:
              {pmod_desc: Pmod_structure(structure)} as moduleExpression,
          } as moduleBinding,
        ),
    } as structureItem => {
      ...structureItem,
      pstr_desc:
        Pstr_module({
          ...moduleBinding,
          pmb_expr: {
            ...moduleExpression,
            pmod_desc:
              Pmod_structure(
                structure
                |> List.map(structureItem =>
                     implementionMapStructureItem(
                       switch (key) {
                       | TopLevel => Nested([|moduleName|])
                       | Nested(keys) =>
                         Nested(Array.concat([keys, [|moduleName|]]))
                       },
                       mapper,
                       structureItem,
                     )
                   ),
              ),
          },
        }),
    }
  | {
      pstr_desc:
        Pstr_value(
          recFlag,
          [
            {
              pvb_pat: {ppat_desc: Ppat_var({txt: "make"})},
              pvb_expr: expression,
            } as value,
          ],
        ),
    } as letBinding =>
    let foundReturnComponent = ref(false);
    let rec mapBody = expression =>
      switch (expression) {
      | {
          pexp_desc:
            Pexp_fun(Nolabel, None, {ppat_desc: Ppat_any} as pattern, body),
        } as item => {
          ...item,
          pexp_desc: Pexp_fun(Nolabel, None, pattern, mapBody(body)),
        }
      | {pexp_desc: Pexp_fun(label, defaultValue, pattern, body)} as item => {
          ...item,
          pexp_desc: Pexp_fun(label, defaultValue, pattern, mapBody(body)),
        }
      | {pexp_desc: Pexp_let(recFlag, valueBindings, next)} as item => {
          ...item,
          pexp_desc: Pexp_let(recFlag, valueBindings, mapBody(next)),
        }
      | {
          pexp_desc:
            Pexp_record(
              items,
              Some({pexp_desc: Pexp_ident({txt: Lident("component")})}),
            ),
        } as record =>
        foundReturnComponent := true;

        switch (items) {
        | [
            (
              {txt: Lident("render")},
              {
                pexp_desc:
                  Pexp_fun(Nolabel, None, {ppat_desc: Ppat_any}, body),
              },
            ),
          ] => body
        | [
            (
              {txt: Lident("didMount")},
              {
                pexp_desc:
                  Pexp_fun(
                    Nolabel,
                    None,
                    {ppat_desc: Ppat_any},
                    didMountBody,
                  ),
              },
            ),
            (
              {txt: Lident("render")},
              {
                pexp_desc:
                  Pexp_fun(Nolabel, None, {ppat_desc: Ppat_any}, body),
              },
            ),
          ] => {
            pexp_loc: Location.none,
            pexp_attributes: [],
            pexp_desc:
              Pexp_sequence(
                {
                  pexp_loc: Location.none,
                  pexp_attributes: [],
                  pexp_desc:
                    Pexp_apply(
                      {
                        pexp_desc:
                          Pexp_ident({
                            txt: Lident("React.useEffect0"),
                            loc: Location.none,
                          }),
                        pexp_loc: Location.none,
                        pexp_attributes: [],
                      },
                      [
                        (
                          Nolabel,
                          {
                            pexp_desc:
                              Pexp_fun(
                                Nolabel,
                                None,
                                {
                                  ppat_loc: Location.none,
                                  ppat_attributes: [],
                                  ppat_desc:
                                    Ppat_construct(
                                      {
                                        loc: Location.none,
                                        txt: Lident("()"),
                                      },
                                      None,
                                    ),
                                },
                                didMountBody,
                              ),
                            pexp_loc: Location.none,
                            pexp_attributes: [],
                          },
                        ),
                      ],
                    ),
                },
                body,
              ),
          }
        | [
            (
              {txt: Lident("initialState")},
              {
                pexp_desc:
                  Pexp_fun(
                    Nolabel,
                    None,
                    {ppat_desc: Ppat_construct({txt: Lident("()")}, None)},
                    _,
                  ) as initialStateFunc,
              },
            ),
            (
              {txt: Lident("reducer")},
              {pexp_desc: Pexp_fun(Nolabel, None, _, _) as reducerFunc},
            ),
            (
              {txt: Lident("render")},
              {
                pexp_desc:
                  Pexp_fun(
                    Nolabel,
                    None,
                    {ppat_desc: Ppat_record(renderDestruct, _)},
                    body,
                  ),
              },
            ),
          ]
            when
              List.length(
                renderDestruct
                |> List.filter((({txt}, _)) => {
                     Console.log(txt);
                     txt == Lident("send") || txt == Lident("state");
                   }),
              )
              == List.length(renderDestruct) => {
            pexp_loc: Location.none,
            pexp_attributes: [],
            pexp_desc:
              Pexp_let(
                Nonrecursive,
                [
                  {
                    pvb_pat: {
                      ppat_desc:
                        Ppat_tuple([
                          {
                            ppat_desc:
                              Ppat_var({txt: "state", loc: Location.none}),
                            ppat_loc: Location.none,
                            ppat_attributes: [],
                          },
                          {
                            ppat_desc:
                              Ppat_var({txt: "send", loc: Location.none}),
                            ppat_loc: Location.none,
                            ppat_attributes: [],
                          },
                        ]),
                      ppat_loc: Location.none,
                      ppat_attributes: [],
                    },
                    pvb_expr: {
                      pexp_loc: Location.none,
                      pexp_attributes: [],
                      pexp_desc:
                        Pexp_apply(
                          {
                            pexp_desc:
                              Pexp_ident({
                                txt:
                                  Lident(
                                    "ReactUpdate.useReducerWithMapState",
                                  ),
                                loc: Location.none,
                              }),
                            pexp_loc: Location.none,
                            pexp_attributes: [],
                          },
                          [
                            (
                              Nolabel,
                              {
                                pexp_desc: initialStateFunc,
                                pexp_loc: Location.none,
                                pexp_attributes: [],
                              },
                            ),
                            (
                              Nolabel,
                              {
                                pexp_desc: reducerFunc,
                                pexp_loc: Location.none,
                                pexp_attributes: [],
                              },
                            ),
                          ],
                        ),
                    },
                    pvb_attributes: [],
                    pvb_loc: Location.none,
                  },
                ],
                body,
              ),
          }
        | _ => {
            pexp_loc: Location.none,
            pexp_attributes: [],
            pexp_desc:
              Pexp_apply(
                {
                  pexp_desc:
                    Pexp_ident({
                      txt: Lident("ReactCompat.useRecordApi"),
                      loc: Location.none,
                    }),
                  pexp_loc: Location.none,
                  pexp_attributes: [],
                },
                [
                  (
                    Nolabel,
                    {
                      ...record,
                      pexp_desc:
                        Pexp_record(
                          items,
                          Some({
                            pexp_desc:
                              Pexp_ident({
                                txt: Lident("ReactCompat.component"),
                                loc: Location.none,
                              }),
                            pexp_loc: Location.none,
                            pexp_attributes: [],
                          }),
                        ),
                    },
                  ),
                ],
              ),
          }
        };
      | _ as expression => expression
      };

    let body = mapBody(expression);
    let rec mapChildren = expression =>
      switch (expression) {
      | {
          pexp_desc:
            Pexp_fun(Nolabel, None, {ppat_desc: Ppat_any} as pattern, body),
        } as item =>
        if (foundReturnComponent^) {
          childrenUsageMap.contents =
            childrenUsageMap.contents |> StringArrayMap.add(key, false);
          {
            ...item,
            pexp_desc:
              Pexp_fun(
                Nolabel,
                None,
                {
                  ...pattern,
                  ppat_desc:
                    Ppat_construct(
                      {loc: Location.none, txt: Lident("()")},
                      None,
                    ),
                },
                mapChildren(body),
              ),
          };
        } else {
          item;
        }
      | {
          pexp_desc:
            Pexp_fun(
              Nolabel,
              None,
              {ppat_desc: Ppat_var({txt})} as pattern,
              body,
            ),
        } as item
          when txt.[0] == '_' =>
        if (foundReturnComponent^) {
          childrenUsageMap.contents =
            childrenUsageMap.contents |> StringArrayMap.add(key, false);
          {
            ...item,
            pexp_desc:
              Pexp_fun(
                Nolabel,
                None,
                {
                  ...pattern,
                  ppat_desc:
                    Ppat_construct(
                      {loc: Location.none, txt: Lident("()")},
                      None,
                    ),
                },
                mapChildren(body),
              ),
          };
        } else {
          item;
        }
      | {
          pexp_desc:
            Pexp_fun(
              Nolabel,
              None,
              {ppat_desc: Ppat_var({txt})} as pattern,
              body,
            ),
        } as item =>
        if (foundReturnComponent^) {
          childrenUsageMap.contents =
            childrenUsageMap.contents |> StringArrayMap.add(key, true);
          {
            ...item,
            pexp_desc:
              Pexp_fun(
                Labelled("children"),
                None,
                {...pattern, ppat_desc: Ppat_var({loc: Location.none, txt})},
                {
                  ...item,
                  pexp_desc:
                    Pexp_fun(
                      Nolabel,
                      None,
                      {
                        ...pattern,
                        ppat_desc:
                          Ppat_construct(
                            {loc: Location.none, txt: Lident("()")},
                            None,
                          ),
                      },
                      {
                        ...item,
                        pexp_desc:
                          Pexp_let(
                            Nonrecursive,
                            [
                              {
                                pvb_pat: {
                                  ppat_desc:
                                    Ppat_var({loc: Location.none, txt}),
                                  ppat_loc: Location.none,
                                  ppat_attributes: [],
                                },
                                pvb_expr: {
                                  pexp_desc:
                                    Pexp_apply(
                                      {
                                        pexp_desc:
                                          Pexp_ident({
                                            loc: Location.none,
                                            txt:
                                              Lident(
                                                "React.Children.toArray",
                                              ),
                                          }),
                                        pexp_loc: Location.none,
                                        pexp_attributes: [],
                                      },
                                      [
                                        (
                                          Nolabel,
                                          {
                                            pexp_desc:
                                              Pexp_ident({
                                                loc: Location.none,
                                                txt: Lident(txt),
                                              }),
                                            pexp_loc: Location.none,
                                            pexp_attributes: [],
                                          },
                                        ),
                                      ],
                                    ),
                                  pexp_loc: Location.none,
                                  pexp_attributes: [],
                                },
                                pvb_attributes: [],
                                pvb_loc: Location.none,
                              },
                            ],
                            mapChildren(body),
                          ),
                      },
                    ),
                },
              ),
          };
        } else {
          item;
        }
      | {pexp_desc: Pexp_fun(label, defaultValue, pattern, body)} as item => {
          ...item,
          pexp_desc:
            Pexp_fun(label, defaultValue, pattern, mapChildren(body)),
        }
      | {pexp_desc: Pexp_let(recFlag, valueBindings, next)} as item => {
          ...item,
          pexp_desc: Pexp_let(recFlag, valueBindings, mapChildren(next)),
        }
      | _ as expression => expression
      };
    let body = mapChildren(body);
    {
      ...letBinding,
      pstr_desc:
        Pstr_value(
          recFlag,
          [
            {
              ...value,
              pvb_expr: body,
              pvb_attributes:
                foundReturnComponent^
                  ? [
                    (
                      {txt: "react.component", loc: Location.none},
                      PStr([]),
                    ),
                    ...value.pvb_attributes,
                  ]
                  : value.pvb_attributes,
            },
          ],
        ),
    };
  | _ => default_mapper.structure_item(mapper, item)
  };

let rec implementionSecondPassMapStructure = (key, mapper, item) => {
  let mapStructureItem = item => {
    switch (item) {
    | {
        pstr_desc:
          Pstr_module(
            {
              pmb_name: {txt: moduleName},
              pmb_expr:
                {
                  pmod_desc:
                    Pmod_functor(
                      name,
                      moduleType,
                      {pmod_desc: Pmod_structure(structure)} as moduleExpression,
                    ),
                } as functorExpression,
            } as moduleBinding,
          ),
      } as structureItem =>
      Some({
        ...structureItem,
        pstr_desc:
          Pstr_module({
            ...moduleBinding,
            pmb_expr: {
              ...functorExpression,
              pmod_desc:
                Pmod_functor(
                  name,
                  moduleType,
                  {
                    ...moduleExpression,
                    pmod_desc:
                      Pmod_structure(
                        implementionSecondPassMapStructure(
                          switch (key) {
                          | TopLevel => Nested([|moduleName|])
                          | Nested(keys) =>
                            Nested(Array.concat([keys, [|moduleName|]]))
                          },
                          mapper,
                          structure,
                        ),
                      ),
                  },
                ),
            },
          }),
      })
    | {
        pstr_desc:
          Pstr_module(
            {
              pmb_name: {txt: moduleName},
              pmb_expr:
                {pmod_desc: Pmod_structure(structure)} as moduleExpression,
            } as moduleBinding,
          ),
      } as structureItem =>
      Some({
        ...structureItem,
        pstr_desc:
          Pstr_module({
            ...moduleBinding,
            pmb_expr: {
              ...moduleExpression,
              pmod_desc:
                Pmod_structure(
                  implementionSecondPassMapStructure(
                    switch (key) {
                    | TopLevel => Nested([|moduleName|])
                    | Nested(keys) =>
                      Nested(Array.concat([keys, [|moduleName|]]))
                    },
                    mapper,
                    structure,
                  ),
                ),
            },
          }),
      })
    | {
        pstr_desc:
          Pstr_value(
            Nonrecursive,
            [
              {
                pvb_pat: {ppat_desc: Ppat_var({txt: "component"})},
                pvb_expr: expression,
              },
            ],
          ),
      } =>
      None
    | item => Some(item)
    };
  };
  List.fold_right(
    (item, acc) =>
      switch (mapStructureItem(item)) {
      | None => acc
      | Some(item) => [item, ...acc]
      },
    item,
    [],
  );
};

let implementationRefactorMapper = {
  ...default_mapper,
  structure_item: implementionMapStructureItem(TopLevel),
};
let implementationSecondPassRefactorMapper = {
  ...default_mapper,
  structure: implementionSecondPassMapStructure(TopLevel),
};

let rec interfaceMapSignatureItem = (key, mapper, item) =>
  switch (item) {
  | {
      psig_desc:
        Psig_module(
          {
            pmd_name: {txt: moduleName},
            pmd_type:
              {
                pmty_desc:
                  Pmty_functor(
                    name,
                    moduleTypeDef,
                    {pmty_desc: Pmty_signature(signatures)} as moduleType,
                  ),
              } as functorType,
          } as moduleDef,
        ),
    } => {
      ...item,
      psig_desc:
        Psig_module({
          ...moduleDef,
          pmd_type: {
            ...functorType,
            pmty_desc:
              Pmty_functor(
                name,
                moduleTypeDef,
                {
                  ...moduleType,
                  pmty_desc:
                    Pmty_signature(
                      signatures
                      |> List.map(signature =>
                           interfaceMapSignatureItem(
                             switch (key) {
                             | TopLevel => Nested([|moduleName|])
                             | Nested(keys) =>
                               Nested(Array.concat([keys, [|moduleName|]]))
                             },
                             mapper,
                             signature,
                           )
                         ),
                    ),
                },
              ),
          },
        }),
    }
  | {
      psig_desc:
        Psig_module(
          {
            pmd_name: {txt: moduleName},
            pmd_type: {pmty_desc: Pmty_signature(signatures)} as moduleType,
          } as moduleDef,
        ),
    } => {
      ...item,
      psig_desc:
        Psig_module({
          ...moduleDef,
          pmd_type: {
            ...moduleType,
            pmty_desc:
              Pmty_signature(
                signatures
                |> List.map(signature =>
                     interfaceMapSignatureItem(
                       switch (key) {
                       | TopLevel => Nested([|moduleName|])
                       | Nested(keys) =>
                         Nested(Array.concat([keys, [|moduleName|]]))
                       },
                       mapper,
                       signature,
                     )
                   ),
              ),
          },
        }),
    }
  | {
      psig_desc:
        Psig_value(
          {pval_name: {txt: "make"}, pval_type} as valueDescription,
        ),
    } as makeType =>
    let rec returnsAComponent = ({ptyp_desc}) =>
      switch (ptyp_desc) {
      | Ptyp_constr(
          {
            txt:
              Ldot(Lident("ReasonReact"), "componentSpec" | "component") |
              Lapply(_) |
              Lident(_),
          },
          _,
        ) =>
        true
      | Ptyp_arrow(Nolabel, arg, coreType) => returnsAComponent(coreType)
      | Ptyp_arrow(_, arg, coreType) => returnsAComponent(coreType)
      | _ => false
      };
    let doesReturnAComponent = returnsAComponent(pval_type);
    if (doesReturnAComponent) {
      let rec replaceReturnedComponent = ({ptyp_desc} as t) =>
        switch (ptyp_desc) {
        | Ptyp_constr(
            {
              txt:
                Ldot(Lident("ReasonReact"), "componentSpec" | "component") |
                Lapply(_) |
                Lident(_),
            },
            _,
          ) => {
            ...t,
            ptyp_desc:
              Ptyp_constr(
                {loc: Location.none, txt: Ldot(Lident("React"), "element")},
                [],
              ),
          }
        | Ptyp_arrow(Nolabel, arg, coreType) =>
          switch (
            try(Some(childrenUsageMap.contents |> StringArrayMap.find(key))) {
            | _ => None
            }
          ) {
          | Some(true) => {
              ...t,
              ptyp_desc:
                Ptyp_arrow(
                  Labelled("children"),
                  switch (arg) {
                  | {
                      ptyp_desc:
                        Ptyp_constr(
                          {txt: Lident("array")},
                          [
                            {
                              ptyp_desc:
                                Ptyp_constr(
                                  {
                                    txt:
                                      Ldot(
                                        Lident("ReasonReact"),
                                        "reactElement",
                                      ),
                                  },
                                  [],
                                ),
                            },
                          ],
                        ),
                    } => {
                      ...arg,
                      ptyp_desc:
                        Ptyp_constr(
                          {txt: Lident("React.element"), loc: Location.none},
                          [],
                        ),
                    }
                  | _ => arg
                  },
                  {
                    ...t,
                    ptyp_desc:
                      Ptyp_arrow(
                        Nolabel,
                        {
                          ...arg,
                          ptyp_desc:
                            Ptyp_constr(
                              {txt: Lident("unit"), loc: Location.none},
                              [],
                            ),
                        },
                        replaceReturnedComponent(coreType),
                      ),
                  },
                ),
            }
          | _ => {
              ...t,
              ptyp_desc:
                Ptyp_arrow(
                  Nolabel,
                  {
                    ...arg,
                    ptyp_desc:
                      Ptyp_constr(
                        {txt: Lident("unit"), loc: Location.none},
                        [],
                      ),
                  },
                  replaceReturnedComponent(coreType),
                ),
            }
          }

        | Ptyp_arrow(label, arg, coreType) => {
            ...t,
            ptyp_desc:
              Ptyp_arrow(label, arg, replaceReturnedComponent(coreType)),
          }
        | x => t
        };
      {
        ...makeType,
        psig_desc:
          Psig_value({
            ...valueDescription,
            pval_attributes: [
              ({txt: "react.component", loc: Location.none}, PStr([])),
              ...valueDescription.pval_attributes,
            ],
            pval_type: replaceReturnedComponent(valueDescription.pval_type),
          }),
      };
    } else {
      item;
    };
  | _ => item
  };

let rec interfaceMapSignature = (key, mapper, item) => {
  let mapSignatureItem = item =>
    switch (item) {
    | {
        psig_desc:
          Psig_module(
            {
              pmd_name: {txt: moduleName},
              pmd_type:
                {
                  pmty_desc:
                    Pmty_functor(
                      name,
                      moduleTypeDef,
                      {pmty_desc: Pmty_signature(signatures)} as moduleType,
                    ),
                } as functorType,
            } as moduleDef,
          ),
      } =>
      Some({
        ...item,
        psig_desc:
          Psig_module({
            ...moduleDef,
            pmd_type: {
              ...functorType,
              pmty_desc:
                Pmty_functor(
                  name,
                  moduleTypeDef,
                  {
                    ...moduleType,
                    pmty_desc:
                      Pmty_signature(
                        interfaceMapSignature(
                          switch (key) {
                          | TopLevel => Nested([|moduleName|])
                          | Nested(keys) =>
                            Nested(Array.concat([keys, [|moduleName|]]))
                          },
                          mapper,
                          signatures,
                        ),
                      ),
                  },
                ),
            },
          }),
      })
    | {
        psig_desc:
          Psig_module(
            {
              pmd_name: {txt: moduleName},
              pmd_type:
                {pmty_desc: Pmty_signature(signatures)} as moduleType,
            } as moduleDef,
          ),
      } =>
      Some({
        ...item,
        psig_desc:
          Psig_module({
            ...moduleDef,
            pmd_type: {
              ...moduleType,
              pmty_desc:
                Pmty_signature(
                  interfaceMapSignature(
                    switch (key) {
                    | TopLevel => Nested([|moduleName|])
                    | Nested(keys) =>
                      Nested(Array.concat([keys, [|moduleName|]]))
                    },
                    mapper,
                    signatures,
                  ),
                ),
            },
          }),
      })
    | {psig_desc: Psig_value({pval_name: {txt: "component"}})} => None
    | {
        psig_desc:
          Psig_type(
            Recursive,
            [
              {
                ptype_name: {txt: "action" | "state"},
                ptype_kind: Ptype_abstract,
              },
            ],
          ),
      } =>
      None
    | _ => Some(item)
    };
  List.fold_right(
    (item, acc) =>
      switch (mapSignatureItem(item)) {
      | None => acc
      | Some(item) => [item, ...acc]
      },
    item,
    [],
  );
};

let interfaceRefactorMapper = {
  ...default_mapper,
  signature_item: interfaceMapSignatureItem(TopLevel),
};

let interfaceSecondPassRefactorMapper = {
  ...default_mapper,
  signature: interfaceMapSignature(TopLevel),
};

module StringSet = Set.Make(String);

let read = () => {
  let set = ref(StringSet.empty);
  let rec read = () =>
    try(
      {
        set := set^ |> StringSet.add(stdin |> input_line);
        read();
      }
    ) {
    | End_of_file => ()
    };
  read();
  set^;
};

let transform = (args, fileName) =>
  try({
    let outputDir =
      args |> Array.exists(item => item == "--demo") ? "output/" : "";
    let file = fileName |> Filename.remove_extension;
    let ic = open_in_bin(file ++ ".re");
    let lexbuf = Lexing.from_channel(ic);
    let (ast, comments) =
      Reason_toolchain.RE.implementation_with_comments(lexbuf);
    let newAst =
      implementationRefactorMapper.structure(
        implementationRefactorMapper,
        ast,
      );
    let newAst =
      implementationSecondPassRefactorMapper.structure(
        implementationSecondPassRefactorMapper,
        newAst,
      );
    let target = outputDir ++ file ++ ".re";
    let oc = open_out_bin(target);
    if (Sys.file_exists(file ++ ".rei")) {
      let ic = open_in_bin(file ++ ".rei");
      let lexbuf = Lexing.from_channel(ic);
      let (ast, comments) =
        Reason_toolchain.RE.interface_with_comments(lexbuf);
      let newAst =
        interfaceRefactorMapper.signature(interfaceRefactorMapper, ast);
      let newAst =
        interfaceSecondPassRefactorMapper.signature(
          interfaceSecondPassRefactorMapper,
          newAst,
        );
      let target = outputDir ++ file ++ ".rei";
      let oc = open_out_bin(target);
      let formatter = Format.formatter_of_out_channel(oc);
      Reason_toolchain.RE.print_interface_with_comments(
        formatter,
        (newAst, comments),
      );
      Format.print_flush();
      Console.log(
        Pastel.(
          <Pastel>
            logPrefix
            <Pastel backgroundColor=Green color=Black> " Done " </Pastel>
            " "
            target
          </Pastel>
        ),
      );
      close_out(oc);
    };
    let formatter = Format.formatter_of_out_channel(oc);
    Reason_toolchain.RE.print_implementation_with_comments(
      formatter,
      (newAst, comments),
    );
    Format.print_flush();
    Console.log(
      <Pastel>
        logPrefix
        <Pastel backgroundColor=Green color=Black> " Done " </Pastel>
        " "
        target
      </Pastel>,
    );
    close_out(oc);
  }) {
  | error =>
    let outputDir =
      args |> Array.exists(item => item == "--demo") ? "output/" : "";
    let file = fileName |> Filename.remove_extension;
    let target = outputDir ++ file ++ ".re";
    Console.log(
      <Pastel>
        logPrefix
        <Pastel backgroundColor=Red color=White> " Error " </Pastel>
        " "
        target
      </Pastel>,
    );

    let err = Printexc.to_string(error);
    Console.log(err);
  };

let main = () => {
  switch (Sys.argv) {
  | [||]
  | [|"help" | "-help" | "--help"|] =>
    Console.log("upgrade-reason-react");
    Console.log("Helps you migrate ReasonReact from 0.6 to 0.7");
    Console.log("Usage: find src/**/*.re | Upgrade");
    Console.log("Usage: pass a list of .re files you'd like to convert.");
  | args =>
    read()
    |> StringSet.filter(item => Filename.extension(item) == ".re")
    /* Uncomment next line for debug */
    /* && ! String.contains(item, '_') */
    |> StringSet.iter(transform(args));
    Console.log("Done!");
  };
};
