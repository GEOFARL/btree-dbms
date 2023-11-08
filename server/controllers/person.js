import runProgram from '../config/cppApp.js';

// @desc    Create a new person
// @route   POST /api/person/create
// @access  Public
export const createPerson = (req, res) => {
  const { firstName, lastName, city, age } = req.body;
  const program = runProgram(['insert', firstName, lastName, city, age]);

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
    res.send({});
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
    res.send({});
  });
};
