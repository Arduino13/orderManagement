module orders_manager {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.sql;
    requires java.desktop;
    requires junit;
    requires javafx.graphics;

    exports application;
    exports DBwrapper;
    exports HW;
    opens application to javafx.fxml;
}