# Reasonable Codemod

[Follow up my blog for updates!](https://blog.fakenickels.dev)

Currently it will upgrades the `Styles` of `bs-react-native-jsx3-compat` to `reason-react-native`.

### todo

- [x] Style
- [x] Linking
- [ ] Keyboard
- [ ] Animated
- [ ] Image & Packager

### readme yet to be updated

## Installation

```console
$ esy add reasonable-codemod
```

## Usage

```
ls **/*.re | esy x codemod
```

[WIP]

# Structure

`Codemod.re` file contains the main refactor logic. My idea is that after you'll only need to care about modifying that file and leave the rest of the boilerplate untouched.
