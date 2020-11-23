open Reason_parser;
open Reason_toolchain_conf;
open Ast_helper;
open Ast_mapper;
open Asttypes;
open Parsetree;
open Longident;

// for metaquot
module Ast_408 = Reason_migrate_parsetree__Ast_408;
module Migrate_parsetree__Ast_408 = Reason_migrate_parsetree__Ast_408;

let mapper = {
  ...default_mapper,
  expr: (mapper, expr) => {
    switch (expr) {
    | [%expr Style.style([])] =>
      %expr
      Style.style()
    | [%expr style([])] =>
      %expr
      style()
    | [%expr Style.combine([%e? style1], [%e? style2])] =>
      %expr
      Style.array([|[%e style1], [%e style2]|])
    | {
        pexp_desc:
          Pexp_apply(
            {pexp_desc: Pexp_ident({txt: Lident("style")})} as expression,
            [(Nolabel, {pexp_desc: Pexp_construct(_, Some(items))})],
          ),
      } as structure =>
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
             // convert color props
             switch (item) {
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
                               {txt: Lident("String")},
                               Some(value),
                             ),
                         },
                       ),
                     ],
                   ),
             } => (
                 Labelled(propName),
                 value
               )

             // convert float
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

             | [%expr borderStyle(Solid)] => (
                 Labelled("borderStyle"),
                 [%expr `solid],
               )

             // position
             | [%expr position(Absolute)] => (
                 Labelled("position"),
                 [%expr `absolute],
               )
             | [%expr position(Relative)] => (
                 Labelled("position"),
                 [%expr `relative],
               )

             // font size
             | [%expr fontWeight(`Bold)] => (
                 Labelled("fontWeight"),
                 [%expr `bold],
               )
             | [%expr fontWeight(`Normal)] => (
                 Labelled("fontWeight"),
                 [%expr `normal],
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
             | [%expr display(Flex)] => (
                 Labelled("display"),
                 Exp.ident({txt: Lident("`flex"), loc: Location.none}),
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
                             Pexp_construct({txt: Lident("Baseline")}, _),
                         },
                       ),
                     ],
                   ),
               } => (
                 Labelled(name),
                 Exp.ident({txt: Lident("`baseline"), loc: Location.none}),
               )
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [(Nolabel, [%expr Column])],
                   ),
               } => (
                 Labelled(name),
                 [%expr `column],
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

             // Animated and Transform
             | [%expr Transform.makeAnimated(~translateY=[%e? value], ())] => (
                 Labelled("transform"),
                 [%expr [|translateY(~translateY=[%e value])|]],
               )
             | [%expr Transform.makeAnimated(~translateX=[%e? value], ())] => (
                 Labelled("transform"),
                 [%expr [|translateX(~translateX=[%e value])|]],
               )

             // any(Animated(value))
             | {
                 pexp_desc:
                   Pexp_apply(
                     {pexp_desc: Pexp_ident({txt: Lident(name)})},
                     [(Nolabel, [%expr Animated([%e? value])])],
                   ),
               } =>
               Console.log(
                 <Pastel>
                   "Found an animated value, mapping is not 100%. You may need to finish this by hand."
                 </Pastel>,
               );
               let value =
                 switch (value) {
                 | [%expr
                     Animated.value.interpolate(
                       [%e? animatedValue],
                       [%e? args],
                     )
                   ] =>
                   %expr
                   Animated.Interpolation.(
                     [%e animatedValue]->interpolate([%e args])
                   )
                 | _ => [%expr [%e value]->Animated.StyleProp.float]
                 };

               (Labelled(name), value);

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

    // Animation API
    | [%expr Animation.loop(~animation=[%e? value], ())] => [%expr Animation.loop([%e value])]

    | [%expr Platform.os() === Android]
    | [%expr Platform.os() == Android] =>
      %expr
      Platform.os == Platform.android
    | [%expr Platform.os() === IOS(Phone)]
    | [%expr Platform.os() === IOS(Pad)]
    | [%expr Platform.os() === IOS(Tv)]
    | [%expr Platform.os() == IOS(Phone)]
    | [%expr Platform.os() == IOS(Pad)]
    | [%expr Platform.os() == IOS(Tv)] =>
      %expr
      Platform.os == Platform.ios
    | [%expr `Required(Packager.require([%e? value]))]
    | [%expr `Required(BsReactNative.Packager.require([%e? value]))] =>
      %expr
      ReactNative.Image.Source.fromRequired(ReactNative.Packager.require([%e value]))

    | [%expr AsyncStorage.getItem([%e? keyName], ())] =>
      %expr
      AsyncStorage.getItem([%e keyName])
    | [%expr AsyncStorage.setItem([%e? keyName], [%e? keyValue], ())] =>
      %expr
      AsyncStorage.setItem([%e keyName], [%e keyValue])
    | [%expr AsyncStorage.removeItem([%e? keyName], ())] =>
      %expr
      AsyncStorage.removeItem([%e keyName])
    | [%expr Linking.removeEventListener("url", [%e? listener])] =>
      %expr
      Linking.removeEventListener(`url, [%e listener])
    // Should probably check that this is in fact a labelled hitSlop param
    | [%expr
        {
          "top": float_of_int([%e? top]),
          "bottom": float_of_int([%e? bottom]),
          "left": float_of_int([%e? left]),
          "right": float_of_int([%e? right]),
        }
      ] =>
      %expr
      View.edgeInsets(
        ~top=[%e top],
        ~bottom=[%e bottom],
        ~left=[%e left],
        ~right=[%e right],
        ()
      )

    | _ => default_mapper.expr(mapper, expr)
    };
  },

  structure_item: (mapper, structure_item) => {
    switch (structure_item) {
    | [%stri open BsReactNative] => [%stri open ReactNative]
    | _ => default_mapper.structure_item(mapper, structure_item)
    };
  },
};
