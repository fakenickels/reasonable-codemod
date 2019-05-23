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
  (~prop1: 'a, ~prop2: 'b=?, ~prop3: int=?, ~children: React.element, unit) =>
  React.element;
