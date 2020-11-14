open Reason_parser;
open Reason_toolchain_conf;
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

let logPrefix =
  Pastel.(<Pastel backgroundColor=Cyan color=Black> " UpgradeRR " </Pastel>);

let implementationRefactorMapper = {
  ...default_mapper,
  expr: (_mapper, expression) => {
    if(Codemod.match_(expression)) {
      Codemod.mapper(expression)
    } else expression
  },
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
    let target = outputDir ++ file ++ ".re";
    let oc = open_out_bin(target);
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
