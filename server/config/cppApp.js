import path from 'path';
import { spawn, spawnSync } from 'child_process';

export const runProgram = (options) => {
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

export const runProgramSync = (options) => {
  const programPath = path.join(
    path.resolve(),
    '..',
    'dbms',
    'build',
    'program'
  );

  const program = spawnSync(programPath, options);

  return program;
};
