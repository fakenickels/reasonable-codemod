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
  let whoopsCloseButton = style([width(Pct(100.)), alignSelf(Center)]);
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
    style([
      width(Pct(100.)),
      height(Pt(StyleSheet.hairlineWidth)),
      backgroundColor(String("#000")),
      opacity(Float(0.1)),
    ]);
  let name =
    style([
      fontWeight(`_700),
      fontSize(Float(16.)),
      marginBottom(Pt(2.5)),
    ]);
  let email =
    style([
      fontWeight(`_200),
      fontSize(Float(12.)),
      marginVertical(Pt(2.5)),
    ]);
  let sectionWrapper = style([paddingLeft(Pt(15.)), marginTop(Pt(15.))]);
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
    style([
      flexDirection(Row),
      alignItems(Center),
      width(Pct(100.)),
      marginVertical(Pt(10.)),
    ]);
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
    style([
      flexDirection(Row),
      alignItems(Center),
      width(Pct(100.)),
      marginVertical(Pt(10.)),
    ]);
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
    style([flexDirection(Column), width(Pct(80.))]);
  let notificationExplanationText =
    style([fontSize(Float(12.)), fontWeight(`_300)]);
  let notificationSectionWrapper =
    style([
      flexDirection(Row),
      alignItems(Center),
      justifyContent(SpaceBetween),
      paddingRight(Pt(10.)),
      width(Pct(100.)),
    ]);
  let securityButtonWrapper =
    style([
      flexDirection(Row),
      alignItems(Center),
      width(Pct(100.)),
      marginBottom(Pt(10.)),
    ]);
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
    style([
      flex(1.),
      backgroundColor(String("rgba(0, 0, 0, 0.6)")),
      flexDirection(Column),
      justifyContent(Center),
      alignItems(Center),
    ]);
};
