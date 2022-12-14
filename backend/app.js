var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const jwt = require('jsonwebtoken');


var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');

var cardRouter = require('./routes/card');

var actionRouter = require('./routes/action');

var accountRouter = require('./routes/account');

var customerRouter = require('./routes/customer');

var loginRouter =require('./routes/login');
var saldoactionRouter =require('./routes/saldoaction');


var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/login', loginRouter);//login is not protected 

app.use(authenticateToken);

app.use('/', indexRouter);
app.use('/users', usersRouter);

app.use('/card', cardRouter);

app.use('/action', actionRouter);

app.use('/account', accountRouter);

app.use('/customer', customerRouter);
app.use('/saldoaction', saldoactionRouter);

function authenticateToken(req, res, next) {
    const authHeader = req.headers['authorization']
    const token = authHeader && authHeader.split(' ')[1]
  
    console.log("token = "+token);
    if (token == null) return res.sendStatus(401)
  
    jwt.verify(token, process.env.MY_TOKEN, (err, user) => {
      console.log(err)
  
      if (err) return res.sendStatus(403)
  
      req.user = user
  
      next()
    })
  }

module.exports = app;