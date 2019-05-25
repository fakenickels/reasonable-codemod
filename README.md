# Upgrade Reason React

[![Build Status](https://dev.azure.com/mlbli/Upgrade%20ReasonReact/_apis/build/status/bloodyowl.upgrade-reason-react-esy?branchName=master)](https://dev.azure.com/mlbli/Upgrade%20ReasonReact/_build/latest?definitionId=4&branchName=master)

Upgrade your ReasonReact codebase to 0.7.0 (the release with hooks).

## Installation

```console
$ yarn add bloodyowl-upgrade-reason-react
```

## Usage

Run the script

```console
$ find src/**/*.re | upgrade-reason-react.exe
```

Upgrade ReasonReact

```console
$ yarn add reason-react@^0.7.0
```

Change JSX version in `bsconfig.json`

```diff
 "reason": {
-  "react-jsx": 2
+  "react-jsx": 3
 },
```


