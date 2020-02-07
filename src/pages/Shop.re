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

module InsertMyData = [%graphql
  {|

mutation InsertMyDataMutationXxx(
  $email: String!, 
  $licensePlate: String!, 
  $tariffId: Int!, 
) {
  insert_orders(objects: {
    email: $email, 
    license_plate: $licensePlate, 
    tariff_id: $tariffId, 
}) {
    affected_rows
    returning {
      email
      id
      license_plate
      tariff_id
      validFrom
    }
  }
}

|}
];

module GetTariffsQuery = ReasonApolloHooks.Query.Make(GetTariffs);

// See: https://github.com/kepi74/reason-apollo-hooks#add-useLazyQuery-bindings
module InsertMyDataMutation = ReasonApolloHooks.Mutation.Make(InsertMyData);

[@react.component]
let make = () => {
  let ( screamMutation, _simple, _full ) = InsertMyDataMutation.use();
  let (tariffs, _full) = GetTariffsQuery.use();
  let scream = (formData) => {
    screamMutation(
      ~variables=InsertMyData.make(
        ~email=formData##email, 
        ~licensePlate=formData##licensePlate, 
        ~tariffId=(int_of_string(formData##tariffId)),
        ()
      )##variables,
      ()
    )
      |> Js.Promise.then_(result => {
          // switch(result) {
            // | Data(data) => <div>{React.string("Saved!")}</div>
            // | Error(error) => <div>{React.string("ERRA!")}</div>
            // | NoData => <div>{React.string("NO DATA!")}</div>
            _ => <div>{React.string("SOMETHING!")}</div>
          // }
          Js.Promise.resolve()
        })
      |> ignore
  };

  <div>
    <PageHeading text="Znamka shop" />
    <div>
      {switch (tariffs) {
        | NoData => <div>{React.string("No Tariff Data Loaded")}</div>
        | Loading => <div>{React.string("Tariff Data Loading")}</div>
        | Error(_error) => <div>{React.string("Error Loading Tariff Data")}</div> 
        | Data(data) => <OrderForm 
            tariffs=data##tariffs
            onSubmit={scream}
          />
          
        } 
      }
    </div>
  </div>
};
