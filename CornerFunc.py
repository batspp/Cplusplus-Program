# Joshua Battaglia
# 16OCT2022
# Python functions to be called by C++.

import re
import string
import os   # Added in case directory searching is needed in future versions.
import os.path

"""" 
==========USED TO TEST C++ TO PYTHON COMMUNICATION==========
# Prints something.
def printsomething():
	print("Hello from python!")

# You sent me function.
def PrintMe(v):
	print("You sent me: " + v)
	return 100

# Squares a value.
def SquareValue(v):
        return v * v

============================================================"""

# Create list of items and how many sold.
def numberList():

        itemList = []
        count = 1
        allItems = []
        
        with open('CS210_Project_Three_Input_File.txt', 'r') as f:

                
                for line in f:
                        allItems.append(line.strip())
                        if line.strip() not in itemList:
                                itemList.append(line.strip())

                for i in range(len(itemList)):
                        print(itemList[i], allItems.count(itemList[i]))
                        
                        
# Return frequency of an item.
def productCount(p):
        itemList = []
        count = 0
        allItems = []
        
        with open('CS210_Project_Three_Input_File.txt', 'r') as f:

                
                for line in f:
                        allItems.append(line.strip())
                        if line not in itemList:
                                itemList.append(line.strip())

                if p in itemList:
                        count = allItems.count(p)

        return count

# Create frequency file.
def histogram():
        
        itemList = []
        count = 1
        allItems = []
        
        with open('CS210_Project_Three_Input_File.txt', 'r') as f:

                wf = open('frequency.dat', 'w')
                
                for line in f:
                        allItems.append(line.strip())
                        if line not in itemList:
                                itemList.append(line.strip())

                for i in range(len(itemList)):
                        wf.write(itemList[i] + ' ' + str(allItems.count(itemList[i])))

        wf.close()
                        


def bar(p):
        
        times = productCount(p)

        return times * '*'

histogram()
