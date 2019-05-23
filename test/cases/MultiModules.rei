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
  let make:
    (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, 'c) =>
    ReasonReact.componentSpec(
      state,
      state,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      action,
    );
};

module ReducerComponentWithChildren: {
  type action;
  type state;
  let make:
    (
      ~prop1: 'a,
      ~prop2: 'b=?,
      ~prop3: int=?,
      array(ReasonReact.reactElement)
    ) =>
    ReasonReact.component(
      state,
      ReasonReact.noRetainedProps,
      action,
    );
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
  let make:
    (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, 'c) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
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
  let make:
    (
      ~prop1: 'a,
      ~prop2: 'b=?,
      ~prop3: int=?,
      array(ReasonReact.reactElement)
    ) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
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
  let make:
    (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, 'c) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
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
  let make:
    (
      ~prop1: 'a,
      ~prop2: 'b=?,
      ~prop3: int=?,
      array(ReasonReact.reactElement)
    ) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
};


module type X = {
  type t;
};

module Functor: (T: X) => {
  let component:
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
  let make:
    (
      ~prop1: T.t,
      ~prop2: 'b=?,
      ~prop3: int=?,
      array(ReasonReact.reactElement)
    ) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
};

module FunctorWithChildren: (T: X) => {
  let component:
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
  let make:
    (
      ~prop1: T.t,
      ~prop2: 'b=?,
      ~prop3: int=?,
      array(ReasonReact.reactElement)
    ) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
};
