let editButtonLabel =
  AppConfigTypes.themeStyle((~theme) =>
    style([
      fontSize(Float(14.)),
      color(String(theme.text)),
      fontWeight(`_300),
      marginLeft(Pt(5.)),
    ])
  );
