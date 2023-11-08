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
    res.status(201).send(newPerson);
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

// @desc    Modify an existing person
// @route   PATCH /api/person/modify
// @access  Public
export const modifyPerson = (req, res) => {
  const { data, key } = req.body;
  const { id, firstName, lastName, city, age } = data;
  const program = runProgram([
    'modify',
    key,
    id,
    firstName,
    lastName,
    city,
    age,
  ]);
  let response = {};

  program.stdout.on('data', (chunk) => {
    const data = chunk
      .toString()
      .replace('Modified: ', '')
      .replace(/\n/g, '')
      .trim();
    const [id, firstName, lastName, city, age] = data.split(',');
    response = { id, firstName, lastName, city, age };
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    console.log(response, 'response');
    res.send(response);
  });
};

// @desc    Search the person
// @route   GET /api/person/search
// @access  Public
export const searchPerson = (req, res) => {
  const searchKey = req.query.key;

  const program = runProgram(['search', searchKey]);
  let response = {};

  program.stdout.on('data', (chunk) => {
    if (chunk.toString().startsWith('Found:')) {
      const data = chunk
        .toString()
        .replace('Found: ', '')
        .replace(/\n/g, '')
        .trim();
      const [id, firstName, lastName, city, age] = data.split(',');
      response = { id, firstName, lastName, city, age };
    }
  });

  program.stderr.on('data', (data) => {
    console.log('Error:');
    console.error(data.toString());
  });

  program.on('close', (code) => {
    console.log(`Closed with code ${code}`);
    console.log(response, 'response');
    res.send(response);
  });
};
