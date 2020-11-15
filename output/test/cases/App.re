module Styles = {
  open Style;
  let wrapper =
    AppConfigTypes.themeStyle((~theme) =>
      style([flex(1.), backgroundColor(String(theme.secondary400))])
    );
  let whoopsWrapper =
    AppConfigTypes.themeStyle((~theme) =>
      style([
        height(Pt(250.)),
        width(Pct(80.)),
        backgroundColor(String(theme.background)),
        flexDirection(Column),
        justifyContent(SpaceBetween),
        alignItems(Center),
        padding(Pt(15.)),
        borderRadius(5.),
      ])
    );
  let whoopsCloseButton = style(~width=pct((100.)), ~alignSelf=`center);
  let content =
    AppConfigTypes.themeStyle((~theme) =>
      style([
        height(Pct(100.)),
        marginTop(Pt(10.)),
        paddingTop(Pt(15.)),
        borderTopLeftRadius(5.),
        borderTopRightRadius(5.),
        backgroundColor(String(theme.background)),
      ])
    );
  let divider =
    style(
      ~width=pct((100.)),
      ~height=pt((StyleSheet.hairlineWidth)),
      ~backgroundColor=("#000"),
      ~opacity=(0.1),
    );
  let name =
    style(~fontWeight=`_700, ~fontSize=(16.), ~marginBottom=pt((2.5)));
  let email =
    style(~fontWeight=`_200, ~fontSize=(12.), ~marginVertical=pt((2.5)));
  let sectionWrapper = style(~paddingLeft=pt((15.)), ~marginTop=pt((15.)));
  let sectionTitle =
    AppConfigTypes.themeStyle((~theme) =>
      style([
        color(String(theme.text)),
        fontSize(Float(16.)),
        fontWeight(`_700),
        marginBottom(Pt(15.)),
      ])
    );
  let editButtonWrapper =
    style(
      ~flexDirection=`row,
      ~alignItems=`center,
      ~width=pct((100.)),
      ~marginVertical=pt((10.)),
    );
  let editButtonLabel =
    AppConfigTypes.themeStyle((~theme) =>
      style([
        fontSize(Float(14.)),
        color(String(theme.text)),
        fontWeight(`_300),
        marginLeft(Pt(5.)),
      ])
    );
  let exitButtonWrapper =
    style(
      ~flexDirection=`row,
      ~alignItems=`center,
      ~width=pct((100.)),
      ~marginVertical=pt((10.)),
    );
  let exitButtonLabel =
    AppConfigTypes.themeStyle((~theme) =>
      style([
        fontSize(Float(14.)),
        color(String(theme.error)),
        fontWeight(`_300),
        marginLeft(Pt(10.)),
      ])
    );
  let notificationExplanationWrapper =
    style(~flexDirection=`column, ~width=pct((80.)));
  let notificationExplanationText =
    style(~fontSize=(12.), ~fontWeight=`_300);
  let notificationSectionWrapper =
    style(
      ~flexDirection=`row,
      ~alignItems=`center,
      ~justifyContent=`spaceAround,
      ~paddingRight=pt((10.)),
      ~width=pct((100.)),
    );
  let securityButtonWrapper =
    style(
      ~flexDirection=`row,
      ~alignItems=`center,
      ~width=pct((100.)),
      ~marginBottom=pt((10.)),
    );
  let securityButtonLabel =
    AppConfigTypes.themeStyle((~theme) =>
      style([
        fontSize(Float(12.)),
        color(String(theme.text)),
        fontWeight(`_300),
        marginLeft(Pt(10.)),
      ])
    );
  let link =
    AppConfigTypes.themeStyle((~theme) =>
      style([
        fontSize(Float(12.)),
        color(String(theme.text)),
        fontWeight(`_300),
        marginBottom(Pt(15.)),
      ])
    );
  let appVersion =
    AppConfigTypes.themeStyle((~theme) =>
      style([
        fontSize(Float(10.)),
        color(String(theme.text)),
        opacity(Float(0.3)),
        fontWeight(`_300),
        marginBottom(Pt(5.)),
        marginLeft(Pt(15.)),
      ])
    );
  let backdrop =
    style(
      ~flex=1.,
      ~backgroundColor=("rgba(0, 0, 0, 0.6)"),
      ~flexDirection=`column,
      ~justifyContent=`center,
      ~alignItems=`center,
    );
};
