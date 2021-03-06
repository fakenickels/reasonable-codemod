[@react.component]
let make = (~navigation: Nautilus.StackNavigator.commonNavigation('a, 'b)) => {
  module AppConfig = (val AppConfigTypes.useAppConfig());
  let sloganTopStyle = Styles.sloganTop();
  let sloganBottomStyle = Styles.sloganBottom();

  let ({state: onboardingState}, getOnboardingState) =
    AsyncHook.use((~cb, ()) =>
      cb(() => {PersistedKV.OnboardingState.getToken()})
    );

  React.useEffect0(() => {
    getOnboardingState()
    ->Promise.tapOk(data => {
        switch (data) {
        | Some(_) =>
          navigation.push(
            NavigationConfig.ConfigOuterApp.SignUp({skipPreregister: true}),
          )
        | None => ()
        }
      })
    |> ignore;
    None;
  });

  <StackNavigator.Screen navigation>
    {() =>
       <ReactNative.ImageBackground
         style=ReactNative.Style.(style(~flex=1., ()))
         source={AppConfig.images.startupBackground}>
         <AppStatusBar mode=AppStatusBar.Dark />
         <SafeAreaView style=Styles.wrapper>
           <View style=Styles.sloganTopWrapper>
             {switch (AppConfig.sayings.startupSloganTop) {
              | Some(sloganTop) =>
                <>
                  <Logo
                    style=Style.(
                      style([
                        marginLeft(Pt(15.)),
                        width(Pct(30.)),
                        maxHeight(Pt(200.)),
                      ])
                    )
                    mode=Logo.White
                  />
                  <Title style=sloganTopStyle value=sloganTop />
                </>
              | None =>
                <Image
                  style=Style.(
                    style([
                      maxHeight(Pt(80.)),
                      maxWidth(Pct(90.)),
                      marginTop(Pt(30.)),
                      marginLeft(Auto),
                      marginRight(Auto),
                    ])
                  )
                  resizeMode=`contain
                  source={AppConfig.images.logoStartupTop}
                />
              }}
           </View>
           <View style=Styles.actionsWrapper>
             <View
               style=Style.(
                 style([
                   width(Pct(100.)),
                   maxHeight(Pt(400.)),
                   alignItems(Center),
                   justifyContent(FlexStart),
                   // Workaround for the messed up images to ease the floating awkwardness
                   marginBottom(Pt(-10.)),
                 ])
               )>
               <Image
                 source={AppConfig.images.startupLogo}
                 style=Styles.logoStyle
                 resizeMode=`cover
               />
             </View>
             <AppButton
               style={Style.array([|
                 Styles.actionButton,
                 Style.(
                   style([
                     backgroundColor(
                       String(AppConfig.theme.startupButtonBackgroundColor),
                     ),
                   ])
                 ),
               |])}
               mode=`highlight
               onPress={_ => navigation.push(SignIn)}
               text="Entrar"
             />
             <AppButton
               style=Styles.actionButton
               onPress={_ => {
                 switch (onboardingState) {
                 | Data(Some(_data)) =>
                   navigation.push(SignUp({skipPreregister: true}))
                 | _ => navigation.push(SignUp({skipPreregister: false}))
                 }
               }}
               loading={onboardingState->AsyncHook.isLoading}
               disabled={onboardingState->AsyncHook.isLoading}
               text={
                 switch (onboardingState) {
                 | Data(Some(_data)) => "Continuar abertura de conta"
                 | _ => {j|Abrir conta|j}
                 }
               }
               mode=`light
             />
           </View>
           <Egg setps="TTTT" onCatch={easterEgg(~env=AppConfig.env)}>
             <Title
               style=sloganBottomStyle
               value={AppConfig.sayings.startupSloganBottom}
             />
           </Egg>
         </SafeAreaView>
       </ReactNative.ImageBackground>}
  </StackNavigator.Screen>;
};
