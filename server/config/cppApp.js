import path from 'path';
import { spawn } from 'child_process';

const runProgram = (options) => {
  const programPath = path.join(
    path.resolve(),
    '..',
    'dbms',
    'build',
    'program'
  );

  const program = spawn(programPath, options);

  return program;
};

export default runProgram;
