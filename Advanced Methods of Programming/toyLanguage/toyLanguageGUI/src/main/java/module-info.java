module com.example.toylanguagegui {
    opens toyLanguage.cotroller;

    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires com.almasb.fxgl.all;
    requires java.sql;

    opens com.example.toylanguagegui to javafx.fxml;
    exports com.example.toylanguagegui;
    exports toyLanguage;
    exports toyLanguage.cotroller;
}