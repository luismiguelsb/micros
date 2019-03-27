# micros
SO OS DE VERDADE

https://moodle.ece.ufrgs.br/course/view.php?id=10

http://www.ece.ufrgs.br/~fetter/

* SE O SCRIPT INIT NÃO FUNCIONA:
`dos2unix < "oldScript" > "newScript"`



## Comandos básicos
* Adição de usuário

  `useradd -c "Nome por Extenso" -s /bin/bash -m <login>`
  
  `userdel -r <login>` -> caso login tenha sido criado errado
  
  `passwd <login>`
  
  `exit`
  
  `ssh <login>@<galileoname>`
  
  `echo "export PATH=.:$PATH" >> .profile`
  
  `exit`

* Adição de grupo

  `groupadd -r <nome_do_grupo>`
  
  `groupmems -g gpio -a <login>`

* Adição de scripts de inicialização (script na Galileo)

  `cp ~/<nome_do_script> /etc/init.d`
  
  `chmod +x /etc/init.d/<nome_do_script>`
  
  `update-rc.d <nome_do_script> defaults`
  
  `reboot`
  
  `update-rc.d -f <nome_do_script> remove` -> feito ao final do laboratório

* Transferência de arquivos

  `scp <arquivo_no_host> <login>@<galileoname>:`
  
  `scp <login>@<galileoname>:<arquivo_na_galileo> <path_no_host>`
  
* Depuração remota

  `gdbserver <host>:<port> <programa>` -> executado na Galileo
  
  `kdbg -r <nome_galileo>:<port> <programa>` -> executado no host
  
