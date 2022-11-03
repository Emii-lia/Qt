import pandas as pd
import sqlite3 as st
import kivy
from kivy.app import App
from kivy.uix.widget import Widget
from kivy.lang  import Builder
from kivy.core.window import Window
from kivy.factory import Factory
import os

Window.size=(720,480)
Builder.load_file('style.kv')

class MyLayout(Widget):
    global extensions
    extensions = ['.xls','.csv','.xml','.json']

    def selected(self,filename):
        self.ids.path.text = f'{filename[0]}'

    def submited(self,filename):
        global excel_file
        match=False
        for ext in extensions:
            if ext in str(filename[0]):
                excel_file = str(filename[0])
                match=True
                break
        if not match:
            Factory.AlertPopup().open()
        
        else:
            
            # Connecting to db
            file_name = str(filename[0]).split('/')[-1].split('.')[0]
            con = st.connect(f'{file_name}.db')
            
            # Reading files
            
            if '.csv' in excel_file:
                data = pd.read_csv(excel_file)
            elif '.json' in excel_file:
                data = pd.read_json(excel_file)
            elif '.xml' in excel_file:
                data = pd.read_xml(excel_file)
            elif '.xls' in excel_file:
                data = pd.read_excel(excel_file)
            
            # Converting
            
            data.to_sql(name="newTable",con=con,if_exists="replace",index=True)
            
            # os.system('cp myData -t ')
            
            con.commit()
            con.close()
    
    def formatFile(self,filename):
        match=False
        for ext in extensions:
            if ext in str(filename[0]):
                excel_file = str(filename[0])
                match=True
                break
        if not match:
            Factory.AlertPopup().open()
        
        else:
        
            # Connecting to db
            file_name = str(filename[0]).split('/')[-1].split('.')[0]
            con = st.connect(f'{file_name}.db')
            
            # Reading files
            
            if '.csv' in excel_file:
                data = pd.read_csv(excel_file)
            elif '.json' in excel_file:
                data = pd.read_json(excel_file)
            elif '.xml' in excel_file:
                data = pd.read_xml(excel_file)
            elif '.xls' in excel_file:
                data = pd.read_excel(excel_file)
            
            # Converting
            
            data.to_sql(name="newTable",con=con,if_exists="replace",index=True)
            
            con.commit()
            con.close()
            
            try:
                os.system(f"rm ../../Database/projetest.sqlite ; mv {file_name}.db ../../Database/projetest.sqlite")
            except:
                print("Failed to copy :(")
    
class ExcellToDbApp(App):
    def build(self):
        return MyLayout()
    
if __name__ == '__main__':
    ExcellToDbApp().run()