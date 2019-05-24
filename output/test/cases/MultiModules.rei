module ReducerComponent: {
  type action =
    | Tick;
  type state = {count: int};
  let component:
    ReasonReact.componentSpec(
      state,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      action,
    );
  [@react.component]
  let make: (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
};

module ReducerComponentWithChildren: {
  type action;
  type state;
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
  let component:
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
  [@react.component]
  let make: (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
};

module StatelessComponentWithChildren: {
  let component:
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
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
  let component:
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
  [@react.component]
  let make: (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
};

module StatelessComponentWithoutLifecycleWithChildren: {
  let component:
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
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
    let component:
      ReasonReact.componentSpec(
        ReasonReact.stateless,
        ReasonReact.stateless,
        ReasonReact.noRetainedProps,
        ReasonReact.noRetainedProps,
        ReasonReact.actionless,
      );
    [@react.component]
    let make:
      (~prop1: T.t, ~prop2: 'b=?, ~prop3: int=?, unit) => React.element;
  };

module FunctorWithChildren:
  (T: X) =>
   {
    let component:
      ReasonReact.componentSpec(
        ReasonReact.stateless,
        ReasonReact.stateless,
        ReasonReact.noRetainedProps,
        ReasonReact.noRetainedProps,
        ReasonReact.actionless,
      );
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
