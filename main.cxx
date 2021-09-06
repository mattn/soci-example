#include <iostream>
#include <string>
#include <algorithm>

#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

int
main(int argc, char* argv[]) {
  soci::session sql(soci::sqlite3, "foo.db");

  try {
    sql << "drop table test1";
  } catch (soci::soci_error const &) {
  }

  sql <<
    "create table test1 ("
    "    id integer primary key,"
    "    name varchar(100)"
    ")";

  std::vector<std::string> values = { "ふー", "ばー💩" };
  sql << "insert into test1(name) values(:rtext)", soci::use(values);

  int id;
  std::string name;
  int rid = 2;

  sql << "select id, name from test1 where id = :rid",
      soci::into(id), 
      soci::into(name), 
      soci::use(rid);
  std::cout << id << " " << name << std::endl;

  std::string buf;
  std::getline(std::cin, buf);
  sql << "insert into test1(id, name) values(:rid, :rtext)",
      soci::use(3),
      soci::use(buf);

  soci::rowset<soci::row> rs =
    (sql.prepare << "select id, name from test1 order by id");

  soci::rowset<soci::row>::const_iterator it;
  for (it = rs.begin(); it != rs.end(); it++) {
    soci::row const& r1 = (*it);
    id = r1.get<int>(0);
    name = r1.get<std::string>(1);
    std::cout << id << " " << name << std::endl;
  }
  return 0;
}
