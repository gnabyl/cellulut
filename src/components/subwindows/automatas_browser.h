#ifndef AUTOMATASBROWSER_H
#define AUTOMATASBROWSER_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QFormLayout>
#include <QSpinBox>
#include "../../utils/automata_manager.h"
#include "../../utils/database.h"
#include "transitions_browser.h"
#include "neighbors_browser.h"

/**
 * @brief Classe AutomatasCreator permet de créer une pop-up pour configurer un automate
 */
class AutomatasCreator : public QDialog{
    /**
     * @brief transitionsBrowser pointeur contenant l'ensemble des transitions
     */
    TransitionsBrowser* transitionsBrowser;
    /**
     * @brief neighborsBrowser pointeur contenant l'ensemble des voisinages
     */
    NeighborsBrowser* neighborsBrowser;
    /**
     * @brief mainLayout disposition principale
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief fieldsLayout disposotion pour les différents champs
     */
    QFormLayout* fieldsLayout;
    /**
     * @brief nameField disposition pour l'affichage des noms
     */
    QLineEdit* nameField;
    /**
     * @brief nbStatesSpb champ de valeurs numériques du nombre d'états choisis
     */
    QSpinBox* nbStatesSpb;
    /**
     * @brief neighborhoodChooseButton boutton afin de choisir le voisinage
     */
    QPushButton* neighborhoodChooseButton;
    /**
     * @brief transitionChooseButton boutton afin de choisir les transitions
     */
    QPushButton* transitionChooseButton;
    /**
     * @brief validateButton boutton afin de valider nos choix
     */
    QPushButton* validateButton;
    /**
     * @brief initButtons fonction qui permet de connecter les boutons
     */
    void initButtons();
public:
    /**
     * @brief AutomatasCreator constructeur de la pop-up de création d'automates
     * @param parent widget à part duquel est crée AutomatasCreator
     */
    AutomatasCreator(QWidget* parent);
};
/**
 * @brief Classe AutomatasBrowser permet de créer une pop-up pour charger les automates
 */
class AutomatasBrowser : public QDialog {
    Q_OBJECT
    /**
     * @brief mainLayout disposition principale
     */
    QVBoxLayout* mainLayout;
    /**
     * @brief buttonsLayout disposition des boutons
     */
    QHBoxLayout* buttonsLayout;
    /**
     * @brief automatasTable tableau des automates
     */
    QTableWidget* automatasTable;
    /**
     * @brief automatasItems ligne du tableau des automates
     */
    QTableWidgetItem*** automatasItems;
    /**
     * @brief btnChoose, btnCreate boutons pour choisir et créer des automates
     */
    QPushButton *btnChoose, *btnCreate, *btnDelete, *btnSave;
    /**
     * @brief automataCreator pointeur pour l'affichage de la pop-up de création de d'automate
     */
    AutomatasCreator* automataCreator;

    const int TBL_NB_COLS = 4;
    /**
     * @brief initAutomatasTable fonction pour initialiser le tableau des automates
     */
    void initAutomatasTable();
    /**
     * @brief initButtons fonction pour connecter les boutons avec le back-end
     */
    void initButtons();

  public:
    /**
     * @brief AutomatasBrowser constructeur de la pop-up de chargement d'automates
     * @param parent widget à part duquel est crée AutomatasBrowser
     */
    AutomatasBrowser(QWidget* parent);
    ~AutomatasBrowser();

  signals:
    /**
     * @brief automataChanged permet de renseigner l'id automate
     * @param id numéro de l'automate
     */
    void automataChanged(int id);
    /**
     * @brief btnCreateClicked permet d'ouvrir la pop-up de création d'automate
     */
    void btnCreateClicked();

  private slots:
    /**
     * @brief chooseAutomata permet de choisir un automate
     */
    void chooseAutomata();
    /**
     * @brief openAutomataCreator permet d'ouvrir la pop-up de cxréation d'automate
     */
    void openAutomataCreator();
};

#endif // AUTOMATASBROWSER_H
