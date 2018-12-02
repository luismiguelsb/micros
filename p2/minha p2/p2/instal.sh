#gabriel stefaniak niemiec e nicolas eymael da silva

cp eng10032lab06_1 /etc/init.d
cp eng10032lab07_2 /etc/init.d
cp eng10032lab10_2 /etc/init.d

  
chmod +x /etc/init.d/eng10032lab06_1
chmod +x /etc/init.d/eng10032lab07_2
chmod +x /etc/init.d/eng10032lab10_2

update-rc.d eng10032lab06_1 defaults
update-rc.d eng10032lab07_2 defaults
update-rc.d eng10032lab10_2 defaults

reboot
