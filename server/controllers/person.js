import runProgram from '../config/cppApp.js';

// @desc    Create a new person
// @route   POST /api/person/create
// @access  Public
export const createPerson = (req, res) => {
  const { firstName, lastName, city, age } = req.body;
  const program = runProgram(['insert', firstName, lastName, city, age]);
  let newPerson = {};

  program.stdout.on('data', (chunk) => {
    console.log('Output:');
    const data = chunk
      .toString()
      .replace('Inserted: ', '')
      .replace(/\n/g, '')
      .trim();
    const [id, firstName, lastName, city, age] = data.split(',');
    newPerson = { id, firstName, lastName, city, age };
    console.log(newPerson);
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    res.send(newPerson);
  });
};

// @desc    Delete an existing person
// @route   DELETE /api/person/delete
// @access  Public
export const deletePerson = (req, res) => {
  const { firstName } = req.body;

  const program = runProgram(['remove', firstName]);

  program.stdout.on('data', (chunk) => {
    console.log('Output:');
    console.log(chunk.toString());
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    res.send({ firstName });
  });
};

// @desc    Retrieve all people data
// @route   GET /api/person/getAll
// @access  Public
export const getAll = (req, res) => {
  const program = runProgram(['print']);
  const response = [];

  program.stdout.on('data', (chunk) => {
    const data = chunk
      .toString()
      .replace('Printing values...', '')
      .replace('Done!', '')
      .split('\n')
      .filter((line) => line.trim() !== '')
      .map((line) => line.replace(/\n/g, '').trim());

    data.map((line) => {
      const [id, firstName, lastName, city, age] = line.split(',');
      response.push({ id, firstName, lastName, city, age });
    });
    console.log(response);
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    res.send(response);
  });
};
