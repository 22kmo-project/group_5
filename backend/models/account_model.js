const db = require('../database');

const account = {
  getById: function(id, callback) {
    return db.query('select saldo from account where idaccount=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from account', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into account (idaccount,saldo,accounttype) values(?,?,?)',
      [add_data.idaccount, add_data.saldo, add_data.accounttype],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from account where idaccount=?', [id], callback);
  },
  update: function(id, account, callback) {
    return db.query(
      'update account set saldo=?, accounttype=? where idaccount=?',
      [account.saldo, account.accounttype,id],
      callback
    );
  },
  withdraw: function (idaccount, data, callback) {
    let doubleAmount=parseFloat(data.amount);
    return db.query('CALL withdraw(?,?)', [idaccount, doubleAmount], callback);

 
}, 
debit_transfer: function (idaccount, data, callback) {
  let doubleAmount=parseFloat(data.amount);
  return db.query('CALL withdraw(?,?)', [idaccount, doubleAmount], callback);
},
};
module.exports = account;