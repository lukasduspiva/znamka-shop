let s = ReasonReact.string;

[@react.component]
let make = (~tariffs, ~onSubmit) => {
  let (tariffId , setTariffId) = React.useState(() => "");
  let (licensePlate , setLicensePlate) = React.useState(() => "");
  let (validFrom , setValidFrom) = React.useState(() => "");
  let (email , setEmail) = React.useState(() => "");
  let tariffFieldId = "tariff-field-id";
  let licensePlateFieldId = "licensePlate-field-id";
  let validFromFieldId = "validFrom-field-id";
  let emailFieldId = "email-field-id";
  
<form
    onSubmit={
        evt => {
            ReactEvent.Form.preventDefault(evt);
            onSubmit({
              "email": email,
              "validFrom": validFrom,
              "licensePlate": licensePlate,
              "tariffId": tariffId,
            });
        }
    }>
    <div>
      <label htmlFor=tariffFieldId>{React.string("Tariff")}</label>
      <select
        id=tariffFieldId
        onChange={
            (event) => setTariffId(
                event->ReactEvent.Form.target##value
            )
        }
        value=tariffId
      >
        <option value="" disabled=true />
        {tariffs
        |> Array.map((tariff) => 
        <option 
            key=(string_of_int(tariff##id)) 
            value=(string_of_int(tariff##id)) 
        >
        {React.string(
            string_of_int( tariff##price )
        )}
        </option>
      ) |> React.array}
      </select>
      <div>
        <label htmlFor=licensePlateFieldId>{React.string("license_plate")}</label>
        <input type_="text" 
            id=licensePlateFieldId
            value=licensePlate
            onChange={
                (event) => setLicensePlate(
                    event->ReactEvent.Form.target##value
                )
            }
        />
      </div>
      <div>
        <label htmlFor=validFromFieldId>{React.string("validFrom")}</label>
        <input type_="text" 
            id=validFromFieldId
            value=validFrom
            onChange={
                (event) => setValidFrom(
                    event->ReactEvent.Form.target##value
                )
            }
        />
      </div>
      <div>
        <label htmlFor=emailFieldId>{React.string("email")}</label>
        <input type_="text" 
            id=emailFieldId
            value=email
            onChange={
                (event) => setEmail(
                    event->ReactEvent.Form.target##value
                )
            }
        />
      </div>
      <button>{React.string("Send data")}</button>
    </div>
  </form>;
};
