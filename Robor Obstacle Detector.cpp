function sysCall_init()
 RobotBase=sim.getObjectAssociatedWithScript(sim.handle_self) -- this is bubbleRob's
 leftMotor=sim.getObjectHandle("LeftMotor") -- Handle of the left motor
 rightMotor=sim.getObjectHandle("RightMotor") -- Handle of the right motor

 noseSensor=sim.getObjectHandle("FrontUS") -- Handle of the proximity sensor
 minMaxSpeed={50*math.pi/180,300*math.pi/180} -- Min and max speeds for each motor
 backUntilTime=-1 -- Tells whether bubbleRob is in forward or backward mode
 -- Create the custom UI:
 xml = '<ui title="'..sim.getObjectName(RobotBase)..' speed" closeable="false"resizeable="false" activate="false">'..[[
 <hslider minimum="0" maximum="100" on-change="speedChange_callback"
id="1"/>
 <label text="" style="* {margin-left: 300px;}"/>
 </ui>
 ]]
 ui=simUI.create(xml)
 speed=(minMaxSpeed[1]+minMaxSpeed[2])*1.7
 simUI.setSliderValue(ui,1,100*(speed-minMaxSpeed[1])/(minMaxSpeed[2]-minMaxSpeed[1]))

end
function speedChange_callback(ui,id,newVal)
 speed=minMaxSpeed[1]+(minMaxSpeed[2]-minMaxSpeed[1])*newVal/100
end
function sysCall_actuation()
 result=sim.readProximitySensor(noseSensor) -- Read the proximity sensor
 -- If we detected something, we set the backward mode:
 if (result>0) then backUntilTime=sim.getSimulationTime()+0.2 end
 if (backUntilTime<sim.getSimulationTime()) then
 -- When in forward mode, we simply move forward at the desired speed
 sim.setJointTargetVelocity(leftMotor,-speed)
 sim.setJointTargetVelocity(rightMotor,-speed)
 else
 -- When in backward mode, we simply backup in a curve at reduced speed
 sim.setJointTargetVelocity(leftMotor,-speed)
 sim.setJointTargetVelocity(rightMotor,speed)
 end
end
function sysCall_cleanup()
 simUI.destroy(ui)
end



