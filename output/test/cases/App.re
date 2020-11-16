style(
  ~height=pt((250.)),
  ~width=pct((80.)),
  ~backgroundColor=(theme.background),
  ~flexDirection=`column,
  ~justifyContent=`spaceAround,
  ~alignItems=`center,
  ~padding=pt((15.)),
  ~borderRadius=5.,
  (),
);

module Styles = {
  open Style;
  let wrapper =
    AppConfigTypes.themeStyle((~theme) =>
      style(~flex=1., ~backgroundColor=(theme.secondary400), ())
    );
  let whoopsWrapper =
    AppConfigTypes.themeStyle((~theme) =>
      style(
        ~height=pt((250.)),
        ~width=pct((80.)),
        ~backgroundColor=(theme.background),
        ~flexDirection=`column,
        ~justifyContent=`spaceAround,
        ~alignItems=`center,
        ~padding=pt((15.)),
        ~borderRadius=5.,
        (),
      )
    );
  let whoopsCloseButton = style(~width=pct((100.)), ~alignSelf=`center, ());
  let content =
    AppConfigTypes.themeStyle((~theme) =>
      style(
        ~height=pct((100.)),
        ~marginTop=pt((10.)),
        ~paddingTop=pt((15.)),
        ~borderTopLeftRadius=5.,
        ~borderTopRightRadius=5.,
        ~backgroundColor=(theme.background),
        (),
      )
    );
  let divider =
    style(
      ~width=pct((100.)),
      ~height=pt((StyleSheet.hairlineWidth)),
      ~backgroundColor=("#000"),
      ~opacity=(0.1),
      (),
    );
  let name =
    style(~fontWeight=`_700, ~fontSize=(16.), ~marginBottom=pt((2.5)), ());
  let email =
    style(
      ~fontWeight=`_200,
      ~fontSize=(12.),
      ~marginVertical=pt((2.5)),
      (),
    );
  let sectionWrapper =
    style(~paddingLeft=pt((15.)), ~marginTop=pt((15.)), ());
  let sectionTitle =
    AppConfigTypes.themeStyle((~theme) =>
      style(
        ~color=(theme.text),
        ~fontSize=(16.),
        ~fontWeight=`_700,
        ~marginBottom=pt((15.)),
        (),
      )
    );
  let editButtonWrapper =
    style(
      ~flexDirection=`row,
      ~alignItems=`center,
      ~width=pct((100.)),
      ~marginVertical=pt((10.)),
      (),
    );
  let editButtonLabel =
    AppConfigTypes.themeStyle((~theme) =>
      style(
        ~fontSize=(14.),
        ~color=(theme.text),
        ~fontWeight=`_300,
        ~marginLeft=pt((5.)),
        (),
      )
    );
  let exitButtonWrapper =
    style(
      ~flexDirection=`row,
      ~alignItems=`center,
      ~width=pct((100.)),
      ~marginVertical=pt((10.)),
      (),
    );
  let exitButtonLabel =
    AppConfigTypes.themeStyle((~theme) =>
      style(
        ~fontSize=(14.),
        ~color=(theme.error),
        ~fontWeight=`_300,
        ~marginLeft=pt((10.)),
        (),
      )
    );
  let notificationExplanationWrapper =
    style(~flexDirection=`column, ~width=pct((80.)), ());
  let notificationExplanationText =
    style(~fontSize=(12.), ~fontWeight=`_300, ());
  let notificationSectionWrapper =
    style(
      ~flexDirection=`row,
      ~alignItems=`center,
      ~justifyContent=`spaceAround,
      ~paddingRight=pt((10.)),
      ~width=pct((100.)),
      (),
    );
  let securityButtonWrapper =
    style(
      ~flexDirection=`row,
      ~alignItems=`center,
      ~width=pct((100.)),
      ~marginBottom=pt((10.)),
      (),
    );
  let securityButtonLabel =
    AppConfigTypes.themeStyle((~theme) =>
      style(
        ~fontSize=(12.),
        ~color=(theme.text),
        ~fontWeight=`_300,
        ~marginLeft=pt((10.)),
        (),
      )
    );
  let link =
    AppConfigTypes.themeStyle((~theme) =>
      style(
        ~fontSize=(12.),
        ~color=(theme.text),
        ~fontWeight=`_300,
        ~marginBottom=pt((15.)),
        (),
      )
    );
  let appVersion =
    AppConfigTypes.themeStyle((~theme) =>
      style(
        ~fontSize=(10.),
        ~color=(theme.text),
        ~opacity=(0.3),
        ~fontWeight=`_300,
        ~marginBottom=pt((5.)),
        ~marginLeft=pt((15.)),
        (),
      )
    );
  let backdrop =
    style(
      ~flex=1.,
      ~backgroundColor=("rgba(0, 0, 0, 0.6)"),
      ~flexDirection=`column,
      ~justifyContent=`center,
      ~alignItems=`center,
      (),
    );
};
