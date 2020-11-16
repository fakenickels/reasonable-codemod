open Reason_parser;
open Reason_toolchain_conf;
open Ast_helper;
open Ast_mapper;
open Asttypes;
open Parsetree;
open Longident;

let match_ = structure => {
  switch (structure) {
  | {
      pexp_desc:
        Pexp_apply(
          {pexp_desc: Pexp_ident({txt: Lident("style")})},
          [(Nolabel, {pexp_desc: Pexp_construct(_, Some(_))})],
        ),
    } =>
    true
  | _ => false
  };
};

let mapper =
  [@warning "-8"]
  (
    (
      {
        pexp_desc:
          Pexp_apply(
            {pexp_desc: Pexp_ident({txt: Lident("style")})} as expression,
            [(Nolabel, {pexp_desc: Pexp_construct(_, Some(items))})],
          ),
      } as structure,
    ) => {
      let rec mapItems = items => {
        switch (items) {
        | {pexp_desc: Pexp_tuple([prop, construct])} => [
            prop,
            ...mapItems(construct),
          ]
        | {pexp_desc: Pexp_construct(_, Some(items))} => mapItems(items)
        | _ => []
        };
      };

      let items = mapItems(items);

      let items =
        items
        |> List.map(item => {
             switch (item) {
             // convert color props
             | {
                 pexp_desc:
                   Pexp_apply(
                     {
                       pexp_desc:
                         Pexp_ident({
                           txt: Lident("backgroundColor" as propName),
                         }),
                     },
                     [
                       (
                         Nolabel,
                         {pexp_desc: Pexp_construct(_, Some(value))},
                       ),
                     ],
                   ),
               }
             | {
                 pexp_desc:
                   Pexp_apply(
                     {
                       pexp_desc:
                         Pexp_ident({txt: Lident("color" as propName)}),
                     },
                     [
                       (
                         Nolabel,
                         {pexp_desc: Pexp_construct(_, Some(value))},
                       ),
                     ],
                   ),
               } => (
                 Labelled(propName),
                 value,
               )

             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(propName)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct(
                               {txt: Lident("Float")},
                               Some(value),
                             ),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(propName),
                 value,
               )

             // dp/pt props
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(propName)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct(
                               {txt: Lident("Pct" as measure)},
                               Some(value),
                             ),
                         },
                       ),
                     ],
                   ),
               }
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(propName)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct(
                               {txt: Lident("Pt" as measure)},
                               Some(value),
                             ),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(propName),
                 Exp.apply(
                   Exp.ident({
                     txt: Lident(measure |> String.lowercase_ascii),
                     loc: Location.none,
                   }),
                   [(Nolabel, value)],
                 ),
               )
             // generic props
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct({txt: Lident("Auto")}, _),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({txt: Lident("auto"), loc: Location.none}),
               )

             // convert flex props
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct({txt: Lident("Center")}, _),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({txt: Lident("`center"), loc: Location.none}),
               )
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct(
                               {txt: Lident("SpaceAround")},
                               _,
                             ),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({
                   txt: Lident("`spaceAround"),
                   loc: Location.none,
                 }),
               )
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct(
                               {txt: Lident("SpaceBetween")},
                               _,
                             ),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({
                   txt: Lident("`spaceAround"),
                   loc: Location.none,
                 }),
               )
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct({txt: Lident("FlexEnd")}, _),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({txt: Lident("`flexEnd"), loc: Location.none}),
               )
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct({txt: Lident("FlexStart")}, _),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({txt: Lident("`flexStart"), loc: Location.none}),
               )
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc:
                             Pexp_construct({txt: Lident("Column")}, _),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({txt: Lident("`column"), loc: Location.none}),
               )
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [
                       (
                         Nolabel,
                         {
                           pexp_desc: Pexp_construct({txt: Lident("Row")}, _),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({txt: Lident("`row"), loc: Location.none}),
               )

             // Generic match: flex(1.0) to ~flex=1.0
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [(Nolabel, value)],
                   ),
               } => (
                 Labelled(name),
                 value,
               )
             | _ => failwith("Waut")
             }
           });

      {
        ...structure,
        pexp_desc:
          Pexp_apply(
            expression,
            [(Nolabel, Exp.ident({txt: Lident("()"), loc: Location.none}))]
            |> List.append(items),
          ),
      };
    }
  );
