module ReducerComponent: {
  type action =
    | Tick;
  type state = {count: int};

  [@react.component]
  let make: (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
};

module ReducerComponentWithChildren: {
  [@react.component]
  let make:
    (
      ~prop1: 'a,
      ~prop2: 'b=?,
      ~prop3: int=?,
      ~children: React.element,
      unit
    ) =>
    React.element;
};

module StatelessComponent: {
  [@react.component]
  let make: (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
};

module StatelessComponentWithChildren: {
  [@react.component]
  let make:
    (
      ~prop1: 'a,
      ~prop2: 'b=?,
      ~prop3: int=?,
      ~children: React.element,
      unit
    ) =>
    React.element;
};

module StatelessComponentWithoutLifecycle: {
  [@react.component]
  let make: (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
};

module StatelessComponentWithoutLifecycleWithChildren: {
  [@react.component]
  let make:
    (
      ~prop1: 'a,
      ~prop2: 'b=?,
      ~prop3: int=?,
      ~children: React.element,
      unit
    ) =>
    React.element;
};

module type X = {type t;};

module Functor:
  (T: X) =>
   {
    [@react.component]
    let make:
      (~prop1: T.t, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
  };

module FunctorWithChildren:
  (T: X) =>
   {
    [@react.component]
    let make:
      (
        ~prop1: T.t,
        ~prop2: 'b=?,
        ~prop3: int=?,
        ~children: React.element,
        unit
      ) =>
      React.element;
  };
