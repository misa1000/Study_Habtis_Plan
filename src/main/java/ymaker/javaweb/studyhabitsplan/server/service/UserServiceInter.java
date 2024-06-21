package ymaker.javaweb.studyhabitsplan.server.service;

import ymaker.javaweb.studyhabitsplan.pojo.User;

public interface UserServiceInter {
    /**
     * 用户注册
     * @param username
     * @param password
     */
    void register(String username, String password);

    /**
     * 用户登录
     * @param user
     * @return
     */
    public User login(User user);
}
