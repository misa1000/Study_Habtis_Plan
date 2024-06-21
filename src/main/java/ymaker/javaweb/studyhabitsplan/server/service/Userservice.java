package ymaker.javaweb.studyhabitsplan.server.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ymaker.javaweb.studyhabitsplan.server.mapper.UserMapper;

@Service
public class Userservice implements User{
    @Autowired
    public UserMapper userMapper;
    @Override
    public void register(String username, String password) {
                userMapper.insert(username, password);
    }
}
