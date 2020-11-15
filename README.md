# Reasonable Codemod

[Follow up the article for updates!](https://github.com/fakenickels/reasonable-codemod)

Currently it will upgrades the `Styles` of `bs-react-native-jsx3-compat` to `reason-react-native`.

### readme yet to be updated

## Installation

```console
$ yarn add bloodyowl-upgrade-reason-react
```

## Usage

Run the script

```console
$ find src -name "*.re" | yarn Upgrade
$ # or on windows
$ find src -name "*.re" | yarn Upgrade.exe
```

If you've alias `ReasonReact` to `React`, search and replace it back to `ReasonReact`.

Search and replace:

- `ReasonReact.Update` to `Update`
- `ReasonReact.UpdateWithSideEffects` to `UpdateWithSideEffects`
- `ReasonReact.SideEffects` to `SideEffects`
- `ReasonReact.NoUpdate` to `NoUpdate`

Install `reason-react` from this fork's [master branch](https://github.com/bloodyowl/reason-react)

Install those:

```
$ yarn add reason-react-update
$ yarn add reason-react-compat
```

Change JSX version in `bsconfig.json`

```diff
 "reason": {
-  "react-jsx": 2
+  "react-jsx": 3
 },
```

Update places where you use DOM refs (whether use `React.createRef` or `React.useRef` above your components).

Please do check places where you use `handle` code, this might break.

**This script isn't magic**: some heuristics I use are from personal experience and don't match any codebase. That said, it should do the heavy lifting and let you with details that would be hard to solve with an AST transformation. Let the compiler guide you once you ran the script.
