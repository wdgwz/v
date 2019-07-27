# -*- coding=utf-8 -*-
from ctypes import *
from TestMDType import *
import time


class TestMD(object):
	def __init__(self):

		self.d2 = CDLL('QuickLibTestMD.dll')
 


	 
		self.fGetTestData = self.d2.GetTestData
		self.fGetTestData.argtypes = [c_char_p, c_char_p, c_char_p, c_int32]
		self.fGetTestData.restype = c_bool
		
		
		self.fUnGetTestData = self.d2.UnGetTestData
		self.fUnGetTestData.argtypes = []
		self.fUnGetTestData.restype = c_bool		
		

		self.fConnectServer = self.d2.ConnectServer
		self.fConnectServer.argtypes = [c_char_p]
		self.fConnectServer.restype = c_int32
 
		
 
		
  
		self.fGetMD_Tick = self.d2.GetMD_Tick
		self.fGetMD_Tick.argtypes = []
		self.fGetMD_Tick.restype = c_void_p	
		
		                
 
 	                
	
		self.fGetCmd = self.d2.GetCmd
		self.fGetCmd.argtypes = []
		self.fGetCmd.restype = c_void_p	
		
		self.fOnCmd = self.d2.OnCmd
		self.fOnCmd.argtypes = []
		self.fOnCmd.restype = c_int32	
		
	 
		self.fGetUnGetCmdSize = self.d2.GetUnGetCmdSize
		self.fGetUnGetCmdSize.argtypes = []
		self.fGetUnGetCmdSize.restype = c_int32	 	
		
		
 	
 
	
	

	def ConnectServer(self, ipaddress):
		return self.fConnectServer(ipaddress)
	
	def GetTestData(self, instrumentID, begintime, endtime, priceType):
		return self.fGetTestData(instrumentID, begintime , endtime , priceType)
 
	def UnGetTestData(self):
		return self.fUnGetTestData()			
 
		
	#获取回调信息数量
	def GetUnGetCmdSize(self):
		return self.fGetUnGetCmdSize()

	#获取回调信息
	def GetCmd(self):
	        return (self.fGetCmd(),self.fGetCmdContent()) 
	#指令驱动函数
	def OnCmd(self):
		return self.fOnCmd()
	
	# 
	def GetMD_Tick(self):
		return self.fGetMD_Tick()
	
	
	def DeleteMD_Tick(self):
	        self.fDeleteMD_Tick()
	
 
	
	
 