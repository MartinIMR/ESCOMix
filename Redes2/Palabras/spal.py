import threading
import os

data_path = "Data/"
amor = alegria = frustacion = enojo = ira = estres = 0
total = 0

def get_text(fname):
  file = open(fname, "r", encoding="UTF-8")
  file_string = file.read()
  file.close()
  return file_string

def worker(filename):
  print("Hilo "+threading.currentThread().getName()+" abrira archivo:"+filename)
  text = get_text(filename)
  text = text.split()
  text = [word.lower() for word in text]
  for word in text:
      if word == "alegria" or word == "alegría":
        alegria = alegria + 1
      elif word == "amor":
        amor = amor + 1
      elif word == "frustracion" or word == "frustración":
        frustacion = frustacion + 1
      elif word == "enojo":
        enojo = enojo + 1
      elif word == "ira":
        ira = ira + 1
      elif word == "estres" or word == "estrés":
        estres = estres + 1
      total = total + 1

if __name__ == "__main__":
  folder = "textos/"
  for filename in os.listdir(folder): #Open each file
    hilo = threading.Thread(target=worker,args=(folder+filename,))
    hilo.start() 
  PR

