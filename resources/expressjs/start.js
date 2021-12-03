const express = require('express');
const dotenv = require('dotenv');
const bodyParser = require('body-parser');
const userRouter = require('./routes/index');
const cors = require('cors');

const app = express();
app.use(bodyParser.json());
app.use(cors());

const connectDB = require('./config/db');
dotenv.config({ path: './config/config.env' });
connectDB();

app.use('/', userRouter);
app.listen(3000);