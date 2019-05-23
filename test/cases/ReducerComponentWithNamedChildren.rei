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
