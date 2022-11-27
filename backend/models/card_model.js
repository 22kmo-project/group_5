const db = require('../database');

const card = {
  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  add: function(add_data, callback) {   //idcustomer ja idaccount pitää olla jo olemassa
    return db.query(
      'insert into card (idcard,idcustomer,password,idaccount) values(?,?,?,?)',
      [add_data.idcard, add_data.idcustomer, add_data.password, add_data.idaccount],

      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },
  update: function(id, update_data, callback) {
    return db.query(
      'update card set idcustomer=?,password=?, idaccount=? where idcard=?',
      [update_data.idcustomer, update_data.password, update_data.idaccount, id],
      callback
    );
  }
};
module.exports = card;