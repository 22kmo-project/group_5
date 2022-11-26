const db = require('../database');

const action = {
  getById: function(id, callback) {
    return db.query('select idaccount, action_time, amount from action where idaccount=? order by action_time limit 10', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from action', callback);
  },
  add: function(add_data, callback) {
    return db.query(
      'insert into action (idcard,idaccount,action_time,amount) values(?,?,?,?)',
      [add_data.idcard, add_data.idaccount, add_data.action_time, add_data.amount],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from action where idaction=?', [id], callback);
  },
  update: function(id, action, callback) {
    return db.query(
      'update action set idcard=?,idaccount=?, action_time=?, amount=? where idaction=?',
      [action.idcard, action.idaccount, action.action_time, action.amount, id],
      callback
    );
  }
};
module.exports = action;