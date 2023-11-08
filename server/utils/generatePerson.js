import { faker } from '@faker-js/faker';

export default function generatePerson() {
  const firstName = faker.person.firstName();
  const fullName = faker.person.fullName();
  const lastName = fullName.split(' ').slice(1).join('');
  const city = faker.location.city();
  const age = faker.number.int({ min: 10, max: 100 });

  return {
    firstName,
    lastName,
    city,
    age,
  };
}
