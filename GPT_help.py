# -*- coding: utf-8 -*-
"""
Created on Sat Aug 12 14:53:22 2023

@author: Gunbi
"""



import openai
import googletrans
import argparse
from KetGPT import gpt_key

def creat_parsed():
    parser = argparse.ArgumentParser()
    #parser.add_argument_group('term_ru')
    parser.add_argument('-ts', nargs='+', default= ["Нет"])
    #parser.add_argument('-t2')
    return parser

    
    
def info_about(term):
     #print(term)
     
     qw = '''Give a brief definition of the term {0}'''
     qwest_eu = qw.format(term)
     completion = openai.ChatCompletion.create(
     model="gpt-3.5-turbo",
     messages=[
         {"role": "user", "content": "Hello!"},
         # We'll add the reply back in!
         {
           "content": "Hello there! How can I assist you today?",
           "role": "assistant"
         },
         # Now we add our response:
         {"role": "user", "content": qwest_eu},
       ]
    )
     res_eu = completion.choices[0].message.content
     res_ru = trans.translate(res_eu, src="en", dest = 'ru')
     print(res_ru.text)
     
    
     
    

def check_real(first, second):
             
      qw = '''Describe the type of relationship between {0} and {1}. First, give a clear yes or no answer.
        Give a short explanation in 1-2 sentences. '''  
        
      qwest_eu = qw.format(first, second)
      
      completion = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=[
          {"role": "user", "content": "Hello!"},
          # We'll add the reply back in!
          {
            "content": "Hello there! How can I assist you today?",
            "role": "assistant"
          },
          # Now we add our response:
          {"role": "user", "content": qwest_eu},
        ]
      )



      res_eu = completion.choices[0].message.content
      res_ru = trans.translate(res_eu, src="en", dest = 'ru')

      print(res_ru.text)  



openai.api_key = gpt_key()

parser = creat_parsed()
namespace = parser.parse_args()
terms_rus = namespace.ts

    
trans = googletrans.Translator()
res = trans.translate(terms_rus, desr = 'en', src = 'ru')
terms_eu = []




for r in res:
    terms_eu.append(r.text)


terms_len = len(terms_rus)
if terms_len == 2:
    check_real(terms_eu[0], terms_eu[1]);
elif terms_len == 1:
    info_about(terms_eu[0])


