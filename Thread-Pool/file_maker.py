with open("test.txt",'w') as f:
    for i in range (10):
        f.write(str(i) * 1024)
f.close
