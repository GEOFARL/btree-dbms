// @desc    Create a new post
// @route   POST /api/person/create

import runProgram from '../config/cppApp.js';

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
