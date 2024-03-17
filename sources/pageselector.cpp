#include "headers/pageselector.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPdfPageNavigation>
#include <QToolButton>

PageSelector::PageSelector(QWidget *parent)
    : QWidget(parent)
    , m_pageNavigation(nullptr)
{
    layout = new QHBoxLayout(this);

    m_previousPageButton = new QToolButton(this);
    m_previousPageButton->setIcon(QIcon(":/img/images/go-previous-24.png"));
    m_previousPageButton->setEnabled(false);

    m_pageNumberEdit = new QLineEdit(this);
    m_pageNumberEdit->setAlignment(Qt::AlignRight);

    m_pageCountLabel = new QLabel(this);
    m_pageCountLabel->setFixedSize(QSize(50, 30));
    m_pageCountLabel->setText("0");

    m_nextPageButton = new QToolButton(this);
    m_nextPageButton->setIcon(QIcon(":/img/images/go-next-24.png"));
    m_nextPageButton->setEnabled(false);

    layout->addWidget(m_previousPageButton);
    layout->addWidget(m_pageNumberEdit);
    layout->addWidget(m_pageCountLabel);
    layout->addWidget(m_nextPageButton);
}

PageSelector::~PageSelector() {

    delete m_pageNavigation;
    delete m_pageNumberEdit;
    delete m_pageCountLabel;
    delete m_previousPageButton;
    delete m_nextPageButton;
    delete layout;
}

void PageSelector::setPageNavigation(QPdfPageNavigation *pageNavigation)
{
    m_pageNavigation = pageNavigation;

    connect(m_previousPageButton, &QToolButton::clicked, m_pageNavigation, &QPdfPageNavigation::goToPreviousPage);
    connect(m_pageNavigation, &QPdfPageNavigation::canGoToPreviousPageChanged, m_previousPageButton, &QToolButton::setEnabled);

    connect(m_pageNavigation, &QPdfPageNavigation::currentPageChanged, this, &PageSelector::onCurrentPageChanged);
    connect(m_pageNavigation, &QPdfPageNavigation::pageCountChanged, this, [this](int pageCount){
        m_pageCountLabel->setText(QString::fromLatin1("/ %1").arg(pageCount));
    });

    connect(m_pageNumberEdit, &QLineEdit::editingFinished, this, &PageSelector::pageNumberEdited);

    connect(m_nextPageButton, &QToolButton::clicked, m_pageNavigation, &QPdfPageNavigation::goToNextPage);
    connect(m_pageNavigation, &QPdfPageNavigation::canGoToNextPageChanged, m_nextPageButton, &QToolButton::setEnabled);

    onCurrentPageChanged(m_pageNavigation->currentPage());
}

void PageSelector::onCurrentPageChanged(int page)
{
    if (m_pageNavigation->pageCount() == 0)
        m_pageNumberEdit->setText(QString::number(0));
    else
        m_pageNumberEdit->setText(QString::number(page + 1));
}

void PageSelector::pageNumberEdited()
{
    if (!m_pageNavigation)
        return;

    const QString text = m_pageNumberEdit->text();

    bool ok = false;
    const int pageNumber = text.toInt(&ok);

    if (!ok)
        onCurrentPageChanged(m_pageNavigation->currentPage());
    else
        m_pageNavigation->setCurrentPage(qBound(0, pageNumber - 1, m_pageNavigation->pageCount() - 1));
}