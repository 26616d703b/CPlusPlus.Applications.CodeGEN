#include "mainwindow.h"
#include "generatedcodewindow.h"


MainWindow::MainWindow()
{
    // Groupe : Définition de la classe
    m_className = new QLineEdit;

    m_parentClassName = new QLineEdit;

    QFormLayout* definition_layout = new QFormLayout;
    definition_layout->addRow("&Nom :", m_className);
    definition_layout->addRow("Classe &mère :", m_parentClassName);

    QGroupBox* definition_group = new QGroupBox("Définition de la classe");
    definition_group->setLayout(definition_layout);


    // Groupe : Options
    m_addProtections = new QCheckBox("Protéger le &header contre les inclusions multiples");
    m_addProtections->setChecked(true);

    m_generateConstructor = new QCheckBox("Générer un &constructeur par défaut");
    m_generateDestructor = new QCheckBox("Générer un &destructeur");

    QVBoxLayout* options_layout = new QVBoxLayout;
    options_layout->addWidget(m_addProtections);
    options_layout->addWidget(m_generateConstructor);
    options_layout->addWidget(m_generateDestructor);

    QGroupBox* options_group = new QGroupBox("Options");
    options_group->setLayout(options_layout);


    // Groupe : Commentaires
    m_description = new QTextEdit;

    m_package = new QLineEdit;

    m_project = new QLineEdit;

    m_author = new QLineEdit;

    QFormLayout* comments_layout = new QFormLayout;
    comments_layout->addRow("&Description :", m_description);
    comments_layout->addRow("&Package :", m_package);
    comments_layout->addRow("P&rojet :", m_project);
    comments_layout->addRow("&Auteur :", m_author);

    m_comments = new QGroupBox("Ajouter des commentaires");
    m_comments->setCheckable(true);
    m_comments->setChecked(false);
    m_comments->setLayout(comments_layout);


    // Layout : boutons du bas (générer, quitter...)
    m_generate = new QPushButton("&Générer !");

    m_quit = new QPushButton("&Quitter");

    QHBoxLayout* buttons_layout = new QHBoxLayout;
    buttons_layout->setAlignment(Qt::AlignRight);
    buttons_layout->addWidget(m_generate);
    buttons_layout->addWidget(m_quit);


    // Définition du layout principal, du titre de la fenêtre, etc.
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget(definition_group);
    main_layout->addWidget(options_group);
    main_layout->addWidget(m_comments);
    main_layout->addLayout(buttons_layout);

    setLayout(main_layout);
    setWindowTitle("ClassGEN");


    // Connexions des signaux et des slots
    connect(m_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(m_generate, SIGNAL(clicked()), this, SLOT(GenerateCode()));
}

void MainWindow::GenerateCode()
{
    // On vérifie que le m_className de la classe n'est pas vide, sinon on arrête
    if (m_className->text().isEmpty())
    {
        QMessageBox::critical(this,
                              "Erreur",
                              "Veuillez entrer au moins un m_className de classe");

        return; // Arrêt de la méthode
    }

    // Si tout va bien, on génère le code
    QString code;

    if (m_addProtections->isChecked())
    {
        code += "#ifndef " + m_package->text().toUpper().replace('.', '_')
            + "_" + m_project->text().toUpper().remove(' ')
            + "_" + m_className->text().toUpper() + "_H_\n";

        code += "#define " + m_package->text().toUpper().replace('.', '_')
            + "_" + m_project->text().toUpper().remove(' ')
            + "_" + m_className->text().toUpper() + "_H_\n\n";
    }

    if (m_comments->isChecked()) // On a demandé à inclure les commentaires
    {
        code += "/**\nClasse " + m_className->text() + "\n\n";
        code += "@package : " + m_package->text() + "\n";
        code += "@project : " + m_project->text() + "\n";
        code += "@Auteur : " + m_author->text() + "\n";
        code += "@Description :\n" + m_description->toPlainText() + "\n*/\n";
    }

    code += "class " + m_className->text();

    if (!m_parentClassName->text().isEmpty())
    {
        code += " : public " + m_parentClassName->text();
    }

    code += "\n{\n    public:\n";

    if (m_generateConstructor->isChecked())
    {
        code += "        " + m_className->text() + "();\n";
    }

    if (m_generateDestructor->isChecked())
    {
        code += "        ~" + m_className->text() + "();\n";
    }

    code += "\n\n    protected:\n";
    code += "\n\n    private:\n";
    code += "};\n\n";

    if (m_addProtections->isChecked())
    {
        code += "#endif  // !" + m_package->text().toUpper().replace('.', '_')
            + "_" + m_project->text().toUpper().remove(' ')
            + "_" + m_className->text().toUpper() + "_H_\n\n\n";
    }


    // On crée puis affiche la fenêtre qui affichera le code généré, qu'on lui envoie en paramètre
    GeneratedCodeWindow* code_window = new GeneratedCodeWindow(code, this);
    code_window->exec();
}

