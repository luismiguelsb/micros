# micros
SO OS DE VERDADE

https://moodle.ece.ufrgs.br/course/view.php?id=10

http://www.ece.ufrgs.br/~fetter/


--> Adição de grupo
  groupadd -r <nome_do_grupo>
  groupmems -g gpio -a <login>

--> Adição de scripts de inicialização (script na Galileo)
  cp ~/<nome_do_script> /etc/init.d
  chmod +x /etc/init.d/<nome_do_script>
  update-rc.d <nome_do_script> defaults
  reboot
  update-rc.d -f <nome_do_script> remove
  
--> Transferência de arquivos
  scp <arquivo_no_host> <login>@<galileoname>:
  scp <login>@<galileoname>:<arquivo_na_galileo> <path_no_host>
