import { useContext, useEffect, useState } from 'react';
import { PeopleContext } from '../context/PeopleContextProvider';
import { ModifyContext } from '../context/ModificationContextProvider';
import Card from './Card';

const defaultFormData = {
  firstName: '',
  lastName: '',
  city: '',
  age: '',
};

const defaultFormError = {
  firstName: null,
  lastName: null,
  city: null,
  age: null,
};

const AddForm = () => {
  const { state, dispatch: modifyDispatch } = useContext(ModifyContext);
  const { dispatch } = useContext(PeopleContext);

  const [formData, setFormData] = useState(defaultFormData);
  const [formError, setFormError] = useState(defaultFormError);
  const [submitted, setSubmitted] = useState(false);
  const [modificationName, setModificationName] = useState('');

  useEffect(() => {
    if (state.isModifying) {
      setFormData(state.entry);
      setModificationName(state.entry.firstName);
    }
  }, [state]);

  const validateInput = (formData) => {
    let isValid = true;

    if (formData.firstName.trim().length === 0) {
      setFormError((p) => ({ ...p, firstName: 'First name cannot be empty' }));
      isValid = false;
    } else {
      setFormError((p) => ({ ...p, firstName: null }));
    }

    if (formData.lastName.trim().length === 0) {
      setFormError((p) => ({ ...p, lastName: 'Last name cannot be empty' }));
      isValid = false;
    } else {
      setFormError((p) => ({ ...p, lastName: null }));
    }

    if (formData.city.trim().length === 0) {
      setFormError((p) => ({ ...p, city: 'City cannot be empty' }));
      isValid = false;
    } else {
      setFormError((p) => ({ ...p, city: null }));
    }

    if (!formData.age || formData.age.trim().length === 0) {
      setFormError((p) => ({ ...p, age: 'Age cannot be empty' }));
      isValid = false;
    } else if (Number.isNaN(+formData.age)) {
      isValid = false;
      setFormError((p) => ({ ...p, age: 'Invalid age' }));
    } else if (+formData.age < 0 || +formData.age > 130) {
      isValid = false;
      setFormError((p) => ({ ...p, age: 'Age should be between 0 and 130' }));
    } else {
      setFormError((p) => ({ ...p, age: null }));
    }

    return isValid;
  };

  const submitHandler = async (e) => {
    e.preventDefault();
    setSubmitted(true);
    const isValid = validateInput(formData);

    if (!isValid) {
      return;
    }

    try {
      if (!state.isModifying) {
        const response = await fetch(
          'http://localhost:8000/api/person/create',
          {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify(formData),
          }
        );
        const data = await response.json();
        dispatch({ type: 'ADD_PERSON', payload: data });
      } else {
        const response = await fetch(
          'http://localhost:8000/api/person/modify',
          {
            method: 'PATCH',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({
              key: modificationName,
              data: formData,
            }),
          }
        );
        const data = await response.json();
        dispatch({
          type: 'MODIFY_PERSON',
          payload: { key: modificationName, data },
        });
        modifyDispatch({ type: 'NO_MODIFY' });
      }

      setFormData(defaultFormData);
    } catch (err) {
      console.error(err);
    }
  };

  return (
    <Card classNames={'add-form'}>
      <form className="form" onSubmit={submitHandler}>
        {
          <h2 className="form__heading">
            {!state || !state.isModifying
              ? 'Add a new person'
              : 'Modifying the existing person'}
          </h2>
        }

        <div className="form-control">
          <label htmlFor="fName">First Name: </label>
          <input
            type="text"
            name="fName"
            id="fName"
            value={formData.firstName}
            onChange={(e) => {
              let data = { ...formData, firstName: e.target.value };
              setFormData((p) => {
                return { ...p, firstName: e.target.value };
              });
              if (submitted) {
                validateInput(data);
              }
            }}
          />
          {formError.firstName && (
            <p className="form__error">{formError.firstName}</p>
          )}
        </div>

        <div className="form-control">
          <label htmlFor="lName">Last Name: </label>
          <input
            type="text"
            name="lName"
            id="lName"
            value={formData.lastName}
            onChange={(e) => {
              let data = { ...formData, lastName: e.target.value };
              setFormData((p) => {
                return { ...p, lastName: e.target.value };
              });
              if (submitted) {
                validateInput(data);
              }
            }}
          />
          {formError.lastName && (
            <p className="form__error">{formError.lastName}</p>
          )}
        </div>

        <div className="form-control">
          <label htmlFor="city">City: </label>
          <input
            type="text"
            name="city"
            id="city"
            value={formData.city}
            onChange={(e) => {
              let data = { ...formData, city: e.target.value };
              setFormData((p) => {
                return { ...p, city: e.target.value };
              });
              if (submitted) {
                validateInput(data);
              }
            }}
          />
          {formError.city && <p className="form__error">{formError.city}</p>}
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
            onChange={(e) => {
              let data = { ...formData, age: e.target.value };
              setFormData((p) => {
                return { ...p, age: e.target.value };
              });
              if (submitted) {
                validateInput(data);
              }
            }}
          />
          {formError.age && <p className="form__error">{formError.age}</p>}
        </div>

        <button className="form__button">Submit</button>
      </form>
    </Card>
  );
};

export default AddForm;
