const mysql = require('mysql');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'group_5',
  password: 'netpass',
  database: 'bank'
});
module.exports = connection;