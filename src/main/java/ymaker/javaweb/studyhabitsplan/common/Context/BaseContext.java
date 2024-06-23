package ymaker.javaweb.studyhabitsplan.common.Context;

public class BaseContext {

    public static ThreadLocal<String> threadLocal = new ThreadLocal<>();

    public static void setCurrentUsername(String username) {
        threadLocal.set(username);
    }

    public static String getCurrentUsername() {
        return threadLocal.get();
    }

    public static void removeCurrentUsername() {
        threadLocal.remove();
    }

}
