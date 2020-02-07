module GetTariffs = [%graphql
{| query Tariffs {
  tariffs {
    currency
    id
    price
    tariffDuration
  }
}
|}
];


// Check: https://github.com/apollographql/reason-apollo/blob/4b97f82f88892ad9a92b8afe91b5a2c978ffa114/examples/swapi/src/AddPerson.re
module OrdersInsertInput = [%graphql
{|
  mutation insertOrders($email: String!) {
  insert_orders(
    objects: { email: $email, license_plate: "", tariff_id: 10, validFrom: "" }
  ) {
    returning {
      email
      id
      license_plate
      tariff_id
      validFrom
    }
  }
}
|}];

module OrdersInsertInputMutation = 
  ReasonApollo.CreateMutation(OrdersInsertInput);

module GetTariffsQuery = ReasonApolloHooks.Query.Make(GetTariffs);

[@react.component]
let make = () => {
  let (tariffs, _full) = GetTariffsQuery.use();
  let insertOrder = OrdersInsertInput.make(~email = "email", ());

  <OrdersInsertInputMutation>
    ...{
      (mutation, _result) => {
        <div>
          <PageHeading text="Znamka shop" />
          <div>
            {switch (tariffs) {
              | NoData => <div>{React.string("No Tariff Data Loaded")}</div>
              | Loading => <div>{React.string("Tariff Data Loading")}</div>
              | Error(_error) => <div>{React.string("Error Loading Tariff Data")}</div> 
              | Data(data) => <OrderForm 
                  tariffs=data##tariffs
                  onSubmit={
                    (_formData) =>
                      mutation(
                        ~variables=insertOrder##variables,
                        // ~refetchQueries=[|"getAllUsers"|],
                        (),
                      )
                    |> ignore
                  }
                />
                
              } 
            }
          </div>
        </div>
      }
    }
  </OrdersInsertInputMutation>
};
