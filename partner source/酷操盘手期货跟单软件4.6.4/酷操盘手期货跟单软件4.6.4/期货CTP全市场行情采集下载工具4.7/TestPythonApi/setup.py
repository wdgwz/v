def main():
    from distutils.core import setup
    import py2exe
    #setup(windows = ['QuickLibSimple.pyw'])
    #setup(console = ['QuickLibSimple.py'])
    setup(
    console = [{"script":"QuickLibAShareDemo.py" ,"icon_resources": [(1, "main.ico")]} ]
    ) 
    
    #setup(console = [{"script": "QuickLibDemo.py"}])

    #
    pass

if __name__ == '__main__':
    main()
