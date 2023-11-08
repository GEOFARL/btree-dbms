import express from 'express';
import cors from 'cors';

import personRouter from './routes/person.js';

const PORT = 8000;

const app = express();

app.use(cors());
app.use(express.json());

app.use('/api/person', personRouter);

app.listen(PORT, () => {
  console.log(`Server is started on port ${PORT}`);
});
