#!/usr/bin/python
# -*- coding: utf-8 -*-

import os

os.system("/bin/service postgresql_server start")
os.system("/bin/service postgresql_server on")
#Nedense postgresql-server a ilk start komutu verildiğinde aşağıdaki işlemler geçtiği anda başlamamış oluyor
#ve veritabanı kurulamadan hata verip çıkıyor.Ama iki kere başlattığımda tüm işlemler sorunsuz işliyor.Anladığım kadarıyla burada daha server başlayamadan aşağıdaki işlemlere geçiliyor.Server başladığında aşağıdaki işlemlere geçmeliyim.Şu an nasıl yapacağımı bilmiyorum.Yada buraya boş bir döngü koysam server ın başlayabileceği kadar zaman kazanmış olurum:)
os.system("/bin/service postgresql_server start")
#Burada işlemler postgres kullanıcısı olarak yapılacak.pstgres kullanıcı id si 70
os.setuid(70)
os.system("/usr/bin/createuser -h localhost --createdb --no-createrole --no-superuser kutya")
os.system("/usr/bin/createdb -h localhost --owner kutya kutuphane")
os.system("pg_restore --dbname=kutuphane --host=localhost --port=5432 -U kutya --verbose /tmp/kutyadbV.0.6.7.backup")