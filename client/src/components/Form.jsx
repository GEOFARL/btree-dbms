import { useState } from 'react';

const defaultFormData = {
  firstName: '',
  lastName: '',
  city: '',
  age: null,
};

const Form = () => {
  const [formData, setFormData] = useState(defaultFormData);

  const submitHandler = (e) => {
    e.preventDefault();
  };

  return (
    <form className="form" onSubmit={submitHandler}>
      <h2 className="form__heading">Add new person</h2>

      <div className="form-control">
        <label htmlFor="fName">First Name: </label>
        <input
          type="text"
          name="fName"
          id="fName"
          value={formData.firstName}
          onChange={(e) =>
            setFormData((p) => ({ ...p, firstName: e.target.value }))
          }
        />
      </div>

      <div className="form-control">
        <label htmlFor="lName">Last Name: </label>
        <input
          type="text"
          name="lName"
          id="lName"
          value={formData.lastName}
          onChange={(e) =>
            setFormData((p) => ({ ...p, lastName: e.target.value }))
          }
        />
      </div>

      <div className="form-control">
        <label htmlFor="city">City: </label>
        <input
          type="text"
          name="city"
          id="city"
          value={formData.city}
          onChange={(e) => setFormData((p) => ({ ...p, city: e.target.value }))}
        />
      </div>

      <div className="form-control">
        <label htmlFor="city">Age: </label>
        <input
          type="number"
          name="age"
          id="age"
          min={0}
          max={130}
          value={formData.age}
          onChange={(e) => setFormData((p) => ({ ...p, age: e.target.value }))}
        />
      </div>

      <button className="form__button">Submit</button>
    </form>
  );
};

export default Form;
