
import sqlite3

conn = sqlite3.connect('supervisor.db')

cursor = conn.cursor()

cursor.execute('''
create table if not exists active_devices (
    id int not null auto_increment,
    last_ip varchar(39) not null,

    primary key (id)
)
''')