const db = require('../database');
const bcrypt = require('bcryptjs');


const saltRounds=10;

const card = {
  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  add: function(card, callback){   
    //idcustomer ja idaccount pitää olla jo olemassa
    bcrypt.hash(card.password, saltRounds, function(err, hash){
    return db.query(
      'insert into card (idcard,idcustomer,password,idaccount) values(?,?,?,?)',
      [add_data.idcard, add_data.idcustomer, hash, add_data.idaccount],

      callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },
  update: function(id, card, callback) {
    bcrypt.hash(card.password,saltRounds,function(err, hash){
    return db.query(
      'update card set idcustomer=?,password=?, idaccount=? where idcard=?',
      [update_data.idcustomer, hash, update_data.idaccount, id],
      callback);
  });
  
},
  
  checkPassword: function(idcard,callback){
    return db.query('select password from card where idcard=?',[idcard],callback);
  }
  

};
module.exports = card;